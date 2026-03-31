
typedef struct
{
    int id;
    char nome[100];
    char endereco[100];
    char cpf[15];
    char telefone[12];
    char email[100];
    char sexo;
    char estado_civil[20];
    char data_nasc[11];
} TipoHospede;

typedef struct listaHospedes
{
    TipoHospede Hospedes;
    struct listaHospedes *prox;
} ListaHospede;

/**
 * Percorre a lista por completo para descobrir a quantidade de posições
 * @param lista endereço da lista que será percorrida,
 * @return retorna a quantidade de individuos inseridos
 */
int escolheId(ListaHospede *lista);

ListaHospede *iniciaListaHospede();

int inserirHospede(ListaHospede **lista, TipoHospede hospede);

int buscarHospede(ListaHospede **lista, TipoHospede *hospede, char *cpf, ListaHospede **pos);

void alterarHospede(ListaHospede *pos, TipoHospede hospede);

void apagarHospede(ListaHospede *pos);

void listarHospedes(ListaHospede *lista);
