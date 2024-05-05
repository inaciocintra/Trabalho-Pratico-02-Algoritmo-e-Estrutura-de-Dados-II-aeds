#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define FILE_PATH "/tmp/characters.csv"

#define INITIAL_STRING_CAPACITY 32
#define INITIAL_ARRAY_CAPACITY 5

typedef struct {
    char *id;
    char *name;
    char **alternateNames;
    int alternateNamesCount;
    char *house;
    char *ancestry;
    char *species;
    char *patronus;
    bool isHogwartsStaff;
    bool isHogwartsStudent;
    char *actorName;
    bool isAlive;
    char **alternateActors;
    int alternateActorsCount;
    char *dateOfBirth;
    int yearOfBirth;
    char *eyeColour;
    char *gender;
    char *hairColour;
    bool isWizard;
} Character;

void free_string_array(char **array, int length);
void free_character(Character *character);

char *read_string(int *i, const char *csvLine) {
    int maxSize = strlen(csvLine);
    if (*i >= maxSize) 
        return NULL; 

    int capacity = INITIAL_STRING_CAPACITY;
    char *str = (char *)malloc(capacity * sizeof(char));
    if (str == NULL) {
        perror("Memory allocation error in string");
        return NULL;
    }

    int pos = 0; 
    while (*i < maxSize && csvLine[*i] != ';') 
    {
        if (pos >= capacity-1) {
            capacity *= 2;
            char *temp = (char *)realloc(str, capacity * sizeof(char));
            if (temp == NULL) {
                perror("Error when resizing string");
                free(str); 
                return NULL;
            }
            str = temp;
        }
        str[pos++] = csvLine[(*i)++];
    }

    str[pos] = '\0'; 
    (*i)++;
    return str;
}

char **read_multivalued(int *i, const char *csvLine, int *arrayCount) {
    int maxSize = strlen(csvLine);
    if (*i >= maxSize-1 || csvLine[*i] != '[') 
        return NULL;

    (*i)++; // jump '['

    int arrayCapacity = INITIAL_ARRAY_CAPACITY;
    char **array = (char **)malloc(arrayCapacity * sizeof(char *)); 
    if (array == NULL) {
        perror("Memory allocation error in string array");
        return NULL;
    }

    int pos = 0;
    while (*i < maxSize && csvLine[*i] != ']')
    {
        if (pos >= arrayCapacity) {
            arrayCapacity *= 2; 
            char **temp = (char **)realloc(array, arrayCapacity * sizeof(char *)); 
            if (temp == NULL) {
                perror("Error when resizing string array");
                free_string_array(array, pos);
                return NULL;
            }
            array = temp; 
        }

        int strCapacity = INITIAL_STRING_CAPACITY;
        char *tempStr = (char *)malloc(strCapacity * sizeof(char));
        if (tempStr == NULL) {
            perror("Memory allocation error in string");
            free_string_array(array, pos);
            return NULL;
        }

        int j = 0;
        while (*i < maxSize && csvLine[*i] != ',' && csvLine[*i] != ']')
        {
            if (j >= strCapacity - 1) { 
                strCapacity *= 2;
                char *tempStr2 = (char *)realloc(tempStr, strCapacity * sizeof(char));
                if (tempStr2 == NULL) {
                    perror("Memory reallocation error in string");
                    free_string_array(array, pos);
                    free(tempStr);
                    return NULL;
                }
                tempStr = tempStr2; 
            }
            if (csvLine[*i] != '\'') 
                tempStr[j++] = csvLine[*i];
            
            (*i)++;
        }

        tempStr[j] = '\0'; 
        array[pos++] = tempStr;

        if (csvLine[*i] == ',') 
            (*i)++; 
    }
    (*i) += 2; // jump ']' and ';'
    *arrayCount = pos; 
    return array;
}

bool read_boolean(int *i, const char *csvLine) {
    bool predicate = false;
    char* wordRead = read_string(i, csvLine);

    if (wordRead != NULL) {
        if (wordRead[0] == 'V')
            predicate = true;
        free(wordRead);
    }

    return predicate; 
}

int read_integer(int *i, const char *csvLine){
    char* wordRead = read_string(i, csvLine);
    if(wordRead == NULL)
        return -1;
    return atoi(wordRead);
}

Character* csvLine_mapper(char *csvLine) {
    Character* character = (Character*)malloc(sizeof(Character));
    if (character == NULL) {
        perror("Memory allocation error in Character struct");
        return NULL;
    }

    int i = 0;

    character->id = read_string(&i, csvLine);
    character->name = read_string(&i, csvLine);

    int alternateNamesCount = 0;
    character->alternateNames = read_multivalued(&i, csvLine, &alternateNamesCount);
    character->alternateNamesCount = alternateNamesCount;

    character->house = read_string(&i, csvLine);
    character->ancestry = read_string(&i, csvLine);
    character->species = read_string(&i, csvLine);
    character->patronus = read_string(&i, csvLine);
    character->isHogwartsStaff = read_boolean(&i, csvLine);
    character->isHogwartsStudent = read_boolean(&i, csvLine);
    character->actorName = read_string(&i, csvLine);
    character->isAlive = read_boolean(&i, csvLine);

    int alternateActorsCount = 0;
    character->alternateActors = read_multivalued(&i, csvLine, &alternateActorsCount);
    character->alternateActorsCount = alternateActorsCount;

    character->dateOfBirth = read_string(&i, csvLine);
    character->yearOfBirth = read_integer(&i, csvLine);
    character->eyeColour = read_string(&i, csvLine);
    character->gender = read_string(&i, csvLine);
    character->hairColour = read_string(&i, csvLine);
    character->isWizard = read_boolean(&i, csvLine);
    
    return character; 
}

void print_string_array(char **array, int count) {
    printf("{");
    for (int i = 0; i < count; i++) {
        printf("%s", array[i]);
        if (i < count - 1) {
            printf(", ");
        }
    }
    printf("}");
}

void print_character(Character *character) {
    if (character == NULL) {
        printf("Character struct is NULL.\n");
        return;
    }

    printf("[");
    printf("%s", character->id ? character->id : " "); 
    printf(" ## %s", character->name ? character->name : " ");

    printf(" ## ");
    if (character->alternateNames) 
        print_string_array(character->alternateNames, character->alternateNamesCount);
    else 
        printf(" {}");

    printf(" ## %s", character->house ? character->house : " "); 
    printf(" ## %s", character->ancestry ? character->ancestry : " "); 
    printf(" ## %s", character->species ? character->species : " "); 
    printf(" ## %s", character->patronus ? character->patronus : " "); 
    printf(" ## %s", character->isHogwartsStaff ? "true" : "false"); 
    printf(" ## %s", character->isHogwartsStudent ? "true" : "false"); 
    printf(" ## %s", character->actorName ? character->actorName : " ");
    printf(" ## %s", character->isAlive ? "true" : "false"); 
    printf(" ## %s", character->dateOfBirth ? character->dateOfBirth : " "); 
    printf(" ## %d", character->yearOfBirth); 
    printf(" ## %s", character->eyeColour ? character->eyeColour : " ");
    printf(" ## %s", character->gender ? character->gender : " ");
    printf(" ## %s", character->hairColour ? character->hairColour : " "); 
    printf(" ## %s", character->isWizard ? "true" : "false");

    printf("]\n");
}



// Função para realizar o Counting Sort por um caractere específico
void counting_sort_by_char(Character **characters, int count, int pos) {
    int base = 256; // Considerando a base ASCII
    int countArray[base];
    Character **sortedCharacters = (Character **)malloc(count * sizeof(Character *));
    if (!sortedCharacters) {
        perror("Erro na alocação de memória para sortedCharacters");
        return;
    }
    memset(countArray, 0, sizeof(countArray)); // Inicializa o array de contagem

    // Contagem das ocorrências de cada caractere na posição pos
    for (int i = 0; i < count; i++) {
        int charIndex = characters[i]->id[pos];
        countArray[charIndex]++;
    }

    // Calcula as posições acumuladas
    for (int i = 1; i < base; i++) {
        countArray[i] += countArray[i - 1];
    }

    // Coloca os personagens em ordem de acordo com o caractere na posição pos
    for (int i = count - 1; i >= 0; i--) {
        int charIndex = characters[i]->id[pos];
        sortedCharacters[--countArray[charIndex]] = characters[i];
    }

    // Copia os personagens ordenados de volta para o array original
    for (int i = 0; i < count; i++) {
        characters[i] = sortedCharacters[i];
    }

    // Libera a memória alocada para sortedCharacters
    free(sortedCharacters);
}

// Função para realizar Radix Sort por ID e desempatar pelo nome


// Função para reorganizar o heap
void heapify(Character **characters, int count, int root, int (*compare)(Character*, Character*)) {
    int largest = root; // O maior é inicialmente a raiz
    int left = 2 * root + 1; // Índice do filho à esquerda
    int right = 2 * root + 2; // Índice do filho à direita

    // Verifica se o filho à esquerda é maior que a raiz
    if (left < count && compare(characters[left], characters[largest]) > 0) {
        largest = left;
    }

    // Verifica se o filho à direita é maior que o maior até agora
    if (right < count && compare(characters[right], characters[largest]) > 0) {
        largest = right;
    }

    // Se o maior não é a raiz, troca e continua a heapificar
    if (largest != root) {
        Character *temp = characters[root];
        characters[root] = characters[largest];
        characters[largest] = temp;

        // Heapifica o sub-heap afetado
        heapify(characters, count, largest, compare);
    }
}

// Função para comparar dois personagens com base em hairColour e desempatar por nome
int compare_characters(Character *a, Character *b) {
    // Primeiro compara hairColour
    if (a->hairColour == NULL && b->hairColour != NULL) {
        return -1;
    } else if (a->hairColour != NULL && b->hairColour == NULL) {
        return 1;
    } else if (a->hairColour != NULL && b->hairColour != NULL) {
        int cmp_hairColour = strcmp(a->hairColour, b->hairColour);
        if (cmp_hairColour != 0) {
            return cmp_hairColour;
        }
    }

    // Se hairColour é igual, desempate por nome
    return strcmp(a->name, b->name);
}

// Função Heap Sort para ordenar o array de personagens
void heap_sort_by_hairColour_and_name(Character **characters, int count) {
    // Construir um heap maximo a partir do array de personagens
    for (int i = count / 2 - 1; i >= 0; i--) {
        heapify(characters, count, i, compare_characters);
    }

    // Extrair elementos do heap um a um
    for (int i = count - 1; i > 0; i--) {
        // Mova a raiz para o final
        Character *temp = characters[0];
        characters[0] = characters[i];
        characters[i] = temp;

        // Heapifica a raiz do heap reduzido
        heapify(characters, i, 0, compare_characters);
    }
}


// Função principal que lê o arquivo CSV, processa cada linha, ordena e imprime personagens
int main() {
    // Abre o arquivo CSV para leitura
    

    // Inicializa um array de personagens com alocação dinâmica
    int characterCapacity = INITIAL_ARRAY_CAPACITY;
    int characterCount = 0;
    Character **characterArray = (Character **)malloc(characterCapacity * sizeof(Character *));
    char line[256];
    char codigo[37];
    scanf("%s",codigo);   

    // Lê a linha de cabeçalho (ignorada neste exemplo)
    while (strcmp(codigo,"FIM")!=0)
    {
      FILE *file = fopen(FILE_PATH, "r");
    if (file == NULL) {
        perror("File not found exception.");
        return 1;
        fgets(line, sizeof(line), file);
    }  
    
    
    // Lê cada linha do arquivo e processa
    while (fgets(line, sizeof(line), file)) {
        
        // Mapeia a linha CSV para um objeto Character
        Character *character = csvLine_mapper(line);
        if(strcmp(codigo,character->id)==0){

        // Adiciona o personagem ao array, aumentando a capacidade se necessário
        if (characterCount >= characterCapacity) {
            characterCapacity *= 2;
            Character **newArray = (Character **)realloc(characterArray, characterCapacity * sizeof(Character *));
            if (newArray == NULL) {
                perror("Memory reallocation error for character array");
                free_character(character);
                free(characterArray);
                fclose(file);
                return 1;
            }
            characterArray = newArray;
        }

        // Armazena o personagem no array
        characterArray[characterCount++] = character;
    }
        }
    //le dnv
    scanf("%s",codigo);
    // Fecha o arquivo após a leitura
    fclose(file);
    }

    // Ordena o array de personagens pelo nome usando heap
    heap_sort_by_hairColour_and_name(characterArray, characterCount);
    

    // Imprime todos os personagens armazenados em ordem alfabética de nome
    for (int i = 0; i < 10; i++) {
        print_character(characterArray[i]);
    }

    // Libera a memória alocada para personagens
    for (int i = 0; i < characterCount; i++) {
        free_character(characterArray[i]);
    }

    // Libera o array de personagens
    free(characterArray);

    return 0;
}

// Função para liberar um array de strings
void free_string_array(char **array, int length) {
    if (array == NULL)
        return;

    // Libera cada string do array
    for (int i = 0; i < length; i++) {
        free(array[i]);
    }

    // Libera o próprio array de strings
    free(array);
}

// Função para liberar um objeto Character
void free_character(Character *character) {
    if (character == NULL)
        return;

    // Libera as strings do objeto Character
    free(character->id);
    free(character->name);
    free(character->house);
    free(character->ancestry);
    free(character->species);
    free(character->patronus);
    free(character->actorName);
    free(character->dateOfBirth);
    free(character->eyeColour);
    free(character->gender);
    free(character->hairColour);

    // Libera as listas de strings do objeto Character
    if (character->alternateNames)
        free_string_array(character->alternateNames, character->alternateNamesCount);
    if (character->alternateActors)
        free_string_array(character->alternateActors, character->alternateActorsCount);

    // Libera o próprio objeto Character
    free(character);
}
