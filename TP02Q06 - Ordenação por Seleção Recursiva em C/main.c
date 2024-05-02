#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define FILE_PATH "/tmp/characters.csv"

#define INITIAL_STRING_CAPACITY 32
#define INITIAL_ARRAY_CAPACITY 30
#define  INITIAL_USER_IDS_CAPACITY 30
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
        if (strcmp(wordRead, "VERDADEIRO") == 0)
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

void selection_sort_by_name(Character **characters, int count) {
    for (int i = 0; i < count - 1; i++) {
        // Encontra o índice do personagem com o menor nome no subarray de i a count-1
        int minIndex = i;
        for (int j = i + 1; j < count; j++) {
            if (strcmp(characters[j]->name, characters[minIndex]->name) < 0) {
                minIndex = j;
            }
        }
        // Troca o personagem com o menor nome com o personagem em i
        if (minIndex != i) {
            Character *temp = characters[i];
            characters[i] = characters[minIndex];
            characters[minIndex] = temp;
        }
    }
}

// Função principal que lê o arquivo CSV, processa cada linha, ordena e imprime personagens
int main() {
    int main() {
    // Abre o arquivo CSV para leitura
    FILE *file = fopen(FILE_PATH, "r");
    if (file == NULL) {
        perror("File not found exception.");
        return 1;
    }

    // Inicializa um array de personagens com alocação dinâmica
    int characterCapacity = INITIAL_ARRAY_CAPACITY;
    int characterCount = 0;
    Character **characterArray = (Character **)malloc(characterCapacity * sizeof(Character *));
    if (characterArray == NULL) {
        perror("Memory allocation error for character array");
        fclose(file);
        return 1;
    }

    char line[256];
    // Lê a linha de cabeçalho (ignorada neste exemplo)
    fgets(line, sizeof(line), file);

    // Inicializa um array para armazenar IDs fornecidos pelo usuário
    int userIDsCapacity = INITIAL_USER_IDS_CAPACITY;
    int userIDsCount = 0;
    char **userIDs = (char **)malloc(userIDsCapacity * sizeof(char *));
    if (userIDs == NULL) {
        perror("Memory allocation error for user IDs");
        fclose(file);
        free(characterArray);
        return 1;
    }

    // Lê a entrada do usuário para obter IDs de personagens a serem filtrados até que a entrada seja "FIM"
    char buffer[256];
    while (true) {
        fgets(buffer, sizeof(buffer), stdin);
        // Remove a quebra de linha no final da entrada
        buffer[strcspn(buffer, "\n")] = 0;

        // Se a entrada for "FIM", sai do loop
        if (strcmp(buffer, "FIM") == 0) {
            break;
        }

        // Divide a entrada em tokens (IDs) e armazena em userIDs
        char *token = strtok(buffer, " ");
        while (token != NULL) {
            // Verifica se a capacidade do array de IDs precisa ser aumentada
            if (userIDsCount >= userIDsCapacity) {
                userIDsCapacity *= 2;
                char **newArray = (char **)realloc(userIDs, userIDsCapacity * sizeof(char *));
                if (newArray == NULL) {
                    perror("Memory reallocation error for user IDs");
                    free(userIDs);
                    free(characterArray);
                    fclose(file);
                    return 1;
                }
                userIDs = newArray;
            }
            userIDs[userIDsCount++] = strdup(token);
            token = strtok(NULL, " ");
        }
    }

    // Inicializa um array para armazenar apenas os personagens com os IDs fornecidos pelo usuário
    Character **filteredCharacterArray = (Character **)malloc(characterCapacity * sizeof(Character *));
    if (filteredCharacterArray == NULL) {
        perror("Memory allocation error for filtered character array");
        fclose(file);
        free(characterArray);
        free(userIDs);
        return 1;
    }
    int filteredCharacterCount = 0;

    // Lê cada linha do arquivo e processa
    while (fgets(line, sizeof(line), file)) {
        // Mapeia a linha CSV para um objeto Character
        Character *character = csvLine_mapper(line);

        // Verifica se o personagem tem um dos IDs fornecidos pelo usuário
        bool found = false;
        for (int i = 0; i < userIDsCount; i++) {
            if (strcmp(character->id, userIDs[i]) == 0) {
                found = true;
                break;
            }
        }

        // Se o personagem tiver um dos IDs fornecidos pelo usuário, armazena-o no array filtrado
        if (found) {
            // Verifica se a capacidade do array filtrado precisa ser aumentada
            if (filteredCharacterCount >= characterCapacity) {
                characterCapacity *= 2;
                Character **newArray = (Character **)realloc(filteredCharacterArray, characterCapacity * sizeof(Character *));
                if (newArray == NULL) {
                    perror("Memory reallocation error for filtered character array");
                    free_character(character);
                    free(filteredCharacterArray);
                    free(characterArray);
                    free(userIDs);
                    fclose(file);
                    return 1;
                }
                filteredCharacterArray = newArray;
            }
            filteredCharacterArray[filteredCharacterCount++] = character;
        } else {
            // Libera a memória alocada para o personagem que não está nos IDs fornecidos
            free_character(character);
        }
    }

    // Fecha o arquivo após a leitura
    fclose(file);

    // Ordena o array de personagens filtrados pelo nome usando Selection Sort
    selection_sort_by_name(filteredCharacterArray, filteredCharacterCount);

    // Imprime todos os personagens armazenados em ordem alfabética de nome
    for (int i = 0; i < filteredCharacterCount; i++) {
        print_character(filteredCharacterArray[i]);
    }

    // Libera a memória alocada para personagens filtrados
    for (int i = 0; i < filteredCharacterCount; i++) {
        free_character(filteredCharacterArray[i]);
    }

    // Libera o array de personagens filtrados
    free(filteredCharacterArray);

    // Libera o array de IDs fornecidos pelo usuário
    for (int i = 0; i < userIDsCount; i++) {
        free(userIDs[i]);
    }
    free(userIDs);

    return 0;
}



}