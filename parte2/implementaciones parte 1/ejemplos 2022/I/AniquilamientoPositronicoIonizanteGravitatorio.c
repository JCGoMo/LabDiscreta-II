#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include <stdlib.h>
#include <string.h>
#include "EstructuraGrafo.h"
#include "stdbool.h"
#include <assert.h>

static bool free_tree = true;
static u32 BUCKETS;
u32 aux_cant_lad = 0u;
static u32 delta = 0u;

static void help ()
{
	printf("Uso: \n  \rc \"comentario\" \t\t\t\t\t\t\t\t Agrega un comentario\n \rp edge \"cantidad de vertices\" \"cantidad de lados\" \t\t\t Agrega un grafo\n \re \"identificador del extremo 1\" \"identificador del extremo 2\" \t\t Agrega un lado\n");
}

static void free_list(vertices cl)
{
	vertices aux = NULL;
	aux = cl;
	while (aux->next != NULL)
	{
		cl = cl->next;
		free(aux);
		aux = NULL;
		aux = cl;
	}
	free(cl);
	cl = NULL;
}

static void free_trees(tree ct)
{
	if(ct != NULL)
	{
		free_trees(ct->left);
		free_trees(ct->right);
		free(ct);
		ct = NULL;
	}
}

static u32 pos_elem(Grafo current, u32 name)
{
	u32 hashIndex = 0u;
	hashIndex = hashfunc(name,BUCKETS);
	while(current->G[hashIndex] != NULL)
	{
      if(current->G[hashIndex]->key == name)
         return hashIndex; 
      ++hashIndex;
      hashIndex %= BUCKETS;
   } 
}

static Grafo asign_mem(u32 n,u32 m,Grafo new)
{
	BUCKETS = n;
	new = (GrafoSt *)calloc(1,sizeof(GrafoSt));
	new->G = (vertices *)calloc(n,sizeof(vertices)); 
	for (u32 i = 0; i < n; i++)
	{
		new->G[i] = (vertices)calloc(1,sizeof(struct vertices_aux));
		new->G[i]->is_occupyed = false;
		new->G[i]->next = NULL;
	}
	new->n_vert = n;
	new->m_lad = m;
	new->ord_nat = (tree)calloc(1,sizeof(struct node));
	new->ord_nat->left = NULL;
	new->ord_nat->right = NULL;
	return new;
}

u32 insert(vertices *current,u32 name)
{
	u32 hashIndex = hashfunc(name,BUCKETS);
	while (current[hashIndex]->is_occupyed == true)
	{
		hashIndex++;
		hashIndex %= BUCKETS; 	
	}
	current[hashIndex]->is_occupyed = true;
	current[hashIndex]->key = name;
	current[hashIndex]->next = NULL;
	current[hashIndex]->grad = 0u;
	return hashIndex; 
} 

void add_vert(vertices current,u32 neighbour)
{
	vertices new = NULL;
	current->grad = current->grad + 1;
	if(delta < current->grad)
	{
		delta = current->grad;
	}
	new = (vertices)calloc(1,sizeof(struct vertices_aux));
	new->is_occupyed = true;
	new->key = neighbour;
	new->next = NULL; 
	if (current != NULL)
	{
		vertices aux = current;
		while (aux->next != NULL)
		{
			if (aux->key == neighbour)
			{
				break;
			}
			aux = aux->next;
		}
		if (aux->key != neighbour)
		{
			aux->next = new;
		}
	}else
	{
		current = new;
	}
}

static tree copy_tree(tree cp,bool u,Grafo current)
{
	tree aux = NULL;
	u32 pos;
	if (cp == NULL)
	{
		return NULL;
	}else
	{
		if (u == true)
		{
			aux = (tree)calloc(1,sizeof(struct node));
			aux->name = cp->name;
			aux->nat_ord_indx = cp->nat_ord_indx + 1;
			pos = pos_elem(current,cp->name);
			current->G[pos]->nat_pos = current->G[pos]->nat_pos + 1;
			aux->left = copy_tree(cp->left,u,current);
			aux->right = copy_tree(cp->right,u,current);
		}else
		{
			aux = (tree)calloc(1,sizeof(struct node));
			aux->name = cp->name;
			aux->nat_ord_indx = cp->nat_ord_indx;
			aux->left = copy_tree(cp->left,u,current);
			aux->right = copy_tree(cp->right,u,current);
		}
	}
	return aux;	
}


static u32 insert_to_tree(tree current,u32 name,u32 indx,Grafo graf)
{
	tree aux = NULL;
	tree aux2 = NULL;
	u32 ret = indx;
	if(free_tree == true)
	{
		free_tree = false;
		current->name = name;
		current->nat_ord_indx = 0;
		current->left = NULL;
		current->right = NULL;
		ret = indx;
	}else
	{
		if(current->name > name && current->left == NULL)
		{
			aux = (tree)calloc(1,sizeof(struct node));
			aux->name = name;
			aux->left = NULL;
			aux->right = NULL;
			aux->nat_ord_indx = current->nat_ord_indx;
			ret = aux->nat_ord_indx;
			current->nat_ord_indx++;
			current->left = aux; 
		}else if (current->name > name && current->left != NULL && current->left->name > name)
		{
			ret = insert_to_tree(current->left,name,indx+1,graf);
		}else if (current->name > name && current->left != NULL && current->left->name < name)
		{
			aux2 = copy_tree(current->left,false,graf);
			aux = (tree)calloc(1,sizeof(struct node));
			aux->name = name;
			aux->nat_ord_indx = indx;
			aux->left = aux2;
			aux->right = NULL;
			ret = current->nat_ord_indx; 
			current->left = aux;
		}
		else if(current->name < name && current->right == NULL)
		{
			aux = (tree)calloc(1,sizeof(struct node));
			aux->name = name;
			aux->left = NULL;
			aux->right = NULL;
			aux->nat_ord_indx = current->nat_ord_indx + 1;
			ret = aux->nat_ord_indx;
			current->right = aux;
		}else if ((current->name < name && current->right != NULL && current->right->name < name))
		{
			ret = insert_to_tree(current->right,name,indx + 1,graf) ;
		}else if ((current->name < name && current->right != NULL && current->right->name > name))
		{
			aux2 = copy_tree(current->right,true,graf);
			aux = (tree)calloc(1,sizeof(struct node));
			aux->name = name;
			aux->left = NULL;
			aux->right = aux2;
			aux->nat_ord_indx = current->right->nat_ord_indx;
			ret = current->right->nat_ord_indx;
			current->right = aux;
		}
	}
	return ret;
}

bool exist_vert(u32 vert,tree current)
{
	bool ret = false;
	if(free_tree == false && current != NULL)
	{
		if (current->name == vert)
		{
			ret = true;
			return ret;
		}else if(current->name > vert)
		{
			ret = exist_vert(vert,current->left);
		}else if(current->name < vert)
		{
			ret = exist_vert(vert,current->right);
		}
	}
	return ret;
}


static void cargar_lado(Grafo current,u32 x,u32 y)
{
	u32 indx1 = 0;
	u32 indx2 = 0;
	vertices aux = NULL;
	u32 swp_pos;
	if(aux_cant_lad != 0)
	{
		if(!exist_vert(x,current->ord_nat))
		{
			indx1 = insert(current->G,x); //metemos los vertices en la tabla hash
			current->G[indx1]->nat_pos = insert_to_tree(current->ord_nat,x,0,current);
			add_vert(current->G[indx1],y);
		}else
		{
			indx1 = pos_elem(current,x);
			add_vert(current->G[indx1],y);
		}
		if(!exist_vert(y,current->ord_nat))
		{
			indx2 = insert(current->G,y);
			current->G[indx2]->nat_pos = insert_to_tree(current->ord_nat,y,0,current);
			add_vert(current->G[indx2],x);
		}else
		{
			indx2 = pos_elem(current,y);
			add_vert(current->G[indx2],x);
		}	
	}else
	{
		printf("No se pueden cargar mas lados\n");
	}
	if (indx1 != current->G[indx1]->nat_pos)
	{
		swp_pos = current->G[indx1]->nat_pos;
		aux = current->G[swp_pos];
		current->G[swp_pos] = current->G[indx1];
		current->G[indx1] = aux;
	}
	if (indx2 != current->G[indx2]->nat_pos)
	{
		swp_pos = current->G[indx2]->nat_pos;
		aux = current->G[swp_pos];
		current->G[swp_pos] = current->G[indx2];
		current->G[indx2] = aux;
	}
	current->delta = delta;
}

Grafo ConstruccionDelGrafo()
{
	Grafo new = NULL;
	char *buffer =(char *)calloc(100,sizeof(char));
	char *fields;
	char opcion = ' ';
	u32 x,y;
	bool existe_grafo = false; // El grafo esta creado? NO
	while(fgets(buffer,100,stdin) != NULL) // Recibir datos en el formato DIMACS hasta que se oprima CTRL- D
	{
		opcion = buffer[0];
		omito_espacios:
		if(opcion == 'c')
		{
			//Se omite el comentario
			printf("Comentario cargado\n");
		}else if(opcion == 'p')
		{
			if(existe_grafo == false) // Se revisa si estamos haciendo uso o no de un grafo, para crear uno
			{
				fields = strtok(buffer," "); //Creamos una lista cuyos elementos son los campos de buffer separados por " "
				fields = strtok(NULL, " ");	//Eliminamos el primer elemento de la lista
				if (strcmp(fields,"edge ") ) //Formalidad del formato DIMACS
				{	
					fields = strtok(NULL," ");
					x = atoi(fields);
					if (x == 0 && !strcmp("0",fields))
					//Reviso que lo que se paso no fue una letra ya que atoi asigna 0 a los caracteres
					{
						printf("La linea ingresada no es válida\n");
						help();
						continue;
					}
                    fields = strtok(NULL," ");
					y = atoi(fields);
					if(y == 0 && !strcmp("0",fields))
                    {
    	              	printf("La linea ingresada no es válida\n");
						help();
						continue;
                    }
                    aux_cant_lad = y;
					new = asign_mem(x,y,new);
					existe_grafo = true;
					printf("El grafo ha sido creado de manera exitosa\n");
				}else
				{
					printf("La linea ingresada no es válida\n");
					help();
				}
			}else
			{
				printf("Actualmente tiene un grafo en uso\n");
			}
			//fflush(stdin);
		}else if(opcion == 'e' && existe_grafo == true)
		{
			if(aux_cant_lad > 0)
			{
				fields = strtok(buffer," ");
			    fields = strtok(NULL," ");
				x = atoi(fields);
                if (x == 0 && !strcmp("0",fields))
		    	//Reviso que lo que se paso no fue una letra ya que atoi asigna 0 a los caracteres
	    		{
                    printf("La linea ingresada no es válida\n");
					help();
					continue;
				}
                fields = strtok(NULL," ");
				y = atoi(fields);
			    if(y == 0 && !strcmp("0",fields))
                {
					printf("La linea ingresada no es válida\n");
			        help();
				  	continue;
                }
				cargar_lado(new,x,y);
				if (x == y)
				{
					printf("El lado ingresado ya existe\n");
				}else
				{
					aux_cant_lad--;
					printf("El lado ha sido agregado de manera exitosa\n");
				}
			}else
			{
				printf("No quedan más lados por ingresar\n");
			}
			//fflush(stdin);
		}else if(opcion == 'e' && existe_grafo == false)
		{
			printf("Actualmente no hay ningun grafo cargado\n");
		}else if(opcion == ' ')
		{
			u32 aux = strlen(buffer);
			for (u32 i = 0; i < aux; i++)
			{
				opcion = buffer[i];
				if(opcion != ' ')
				{
					goto omito_espacios;
				}
			}
		}else if(opcion == '\n')
		{
			//fflush(stdin);
			continue;
		}else
		{
			//fflush(stdin);
			printf("La linea ingresada no es válida\n");
			help();
		}
		buffer[0] = '\0'; //Limpio el buffer para la proxima entrada
		fflush(stdin);
	}
	printf("SALIENDO");
	free(buffer);
	buffer = NULL;
	return new;
}    
                        
void DestruccionDelGrafo(Grafo G)
{
	for(int i = 0; i < G->n_vert; i++)
	{
		free_list(G->G[i]);
		G->G[i] = NULL;
	}
	free_trees(G->ord_nat);
	G->ord_nat = NULL;
	free(G->G);
	G->G = NULL;
	free(G);
	G = NULL;
}

u32 NumeroDeVertices(Grafo G)
{
	return G->n_vert;
}
u32 NumeroDeLados(Grafo G)
{
	return G->m_lad;
}

u32 Delta(Grafo G)
{
	return G->delta;
}

u32 Nombre(u32 i,Grafo G)
{
	return G->G[i]->key;
}


u32 Grado(u32 i,Grafo G)
{
	return G->G[i]->grad;
}

u32 IndiceONVecino(u32 j,u32 k,Grafo G)
{
	vertices aux = NULL;
	assert(k < G->n_vert && j < G->G[k]->grad);
	aux = G->G[k];
	for(u32 i = 0; i < j+1;i++)
	{
		aux = aux->next;
	}
	return pos_elem(G,aux->key);
}

