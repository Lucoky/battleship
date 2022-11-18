/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <stdbool.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

enum Orientation {Arriba = 1, Abajo = 2, Izquierda = 3, Derecha = 4}; 

// Inicia una matriz 9x9 en 0.
void InitBattleShip (char array[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int n = 0; n < 9; n++)
        {
            array[i][n] = '0';
        }
    }
}

// Muestra el campo de batalla.
void ShowBatttleField(char battlefield[9][9])
{
    for (int i = 0; i < 10; i++)
    {
        for (int n = 0; n < 10; n++)
        {
            if (i == 0)
            {
                if (n == 0)
                {
                    printf("  ");
                }
                else 
                {
                    printf("%i ", n);        
                }
            }
            else if (n == 0 && i != 0)
            {
                printf("%c ", i + 64);
            }
            else 
            {
                printf("%c ", battlefield[i-1][n-1]);
            }
        }
        
        printf ("\n\r");
    }  
}

// Valida el formato de input.
bool IsValidCoordInput(char coordInput[])
{
    if (coordInput[0] < 'A' || coordInput[0] > 'I')
    {
        return false;
    }
    
    if (coordInput[1] != '-')
    {
        return false;
    }
    
    if (coordInput[2] < '1' || coordInput[2] > '9')
    {
        return false;
    }
    
    return true;
}

// Valida si hay espacio para el barco
bool IsValidCoordPosition(char column, char line, char battlefield[9][9], char shipSize, enum Orientation orientation)
{
    // Validar tamaño.
    switch (orientation)
    {
        case Arriba:
            if (line - shipSize + 1 < 0)
            {
                return false;
            }
            break;
        case Abajo:
            if (line + shipSize > 9)
            {
                return false;
            }
            break;
        case Izquierda:
            if (column + 1 - shipSize < 0)
            {
                return false;
            }
            break;
        case Derecha:
            if (column + shipSize > 9)
            {
                return false;
            }
            break;
    }
    
    // Validar si no hay otro barco ya en ese lugar.
    for (int i = 0; i < shipSize; i++)
    {
        switch (orientation)
        {
        case Arriba:
            if (battlefield[line - i][column] != '0')
            {
                return false;
            }
            break;
        case Abajo:
            if (battlefield[line + i][column] != '0')
            {
                return false;
            }
            break;
        case Izquierda:
            if (battlefield[line][column - i] != '0')
            {
                return false;
            }
            break;
        case Derecha:
            if (battlefield[line][column + i] != '0')
            {
                return false;
            }
            break;
        }
    }
    
    return true;
}

// Inserta un barco en el campo.
void InsertShip(char battlefield[9][9], char column, char line, char shipSize, enum Orientation orientation)
{
    for (int i = 0; i < shipSize; i++)
    {
        switch (orientation)
        {
            case Arriba:
                battlefield[line - i][column] = 'S';
                break;
            case Abajo:
                battlefield[line + i][column] = 'S';
                break;
            case Izquierda:
                battlefield[line][column - i] = 'S';
                break;
            case Derecha:
                battlefield[line][column + i] = 'S';
                break;
            default:
                break;
        }
    }
}

// Obtiene las coordenas de un usuario.
void GetCoordinates(char* line, char* column)
{
    printf("Seleccione las coordenadas(A-1):\n\r");
    bool isValidCoord = false;
    while (!isValidCoord)
    {
        char coord[3];
        scanf("%s", coord);
        getchar();
        isValidCoord = IsValidCoordInput(coord);
        if (!isValidCoord)
        {
           printf("Coordenadas incorrectas respete el formato (Ejemplo: A-1).\n\r"); 
        }
        else
        {
            // Parsea el valor a un int.
            *line = coord[0] - 65;
            *column = coord[2] - 49;
        }
    }
}

// Seleciona en donde y en que posicion se pondra un barco.
void SelectShipPosition(char battlefield[9][9])
{
    bool shipInserted = false;
    do
    {
        // Obtener coordenadas iniciales de barco.
        bool isValidCoord = false;
        char line, column;
        GetCoordinates(&line, &column);
        
        // Obtener orientación.
        printf("Seleccione la dirección:\n\r");
        printf("1-Arriba.\n\r");
        printf("2-Abajo.\n\r");
        printf("3-Izquierda.\n\r");
        printf("4-Derecha.\n\r");
        char orientationInput = getchar();
        getchar();
        while (orientationInput < '1' || orientationInput > '4')
        {
            printf("Seleccione una dirección valida:\n\r");
            orientationInput = getchar();
            getchar();
        }
        
        // Parsear input a enum de orientación.
        enum Orientation orientation = orientationInput - 48;
        shipInserted = IsValidCoordPosition(column, line, battlefield, 3, orientation);
        
        if (shipInserted)
        {
            InsertShip(battlefield, column, line, 3, orientation);
        }
        else
        {
            printf("Posición invalida.\n\r");
        }
    } while (!shipInserted);
}

// Inicia el campo de un jugador.
void InitPlayerBattleShip(char battlefield[9][9])
{
    printf("Elija las coordenadas de todos su barcos.\n\r");
    for (int i = 0; i < 3; i++)
    {
        ShowBatttleField(battlefield);
        SelectShipPosition(battlefield);    
        system("clear");
    }
    printf("Asi quedo su tablero.\n\r");
    ShowBatttleField(battlefield);
}

// Ataca a un tablero.
void Attack(char battlefieldAttecked[9][9], char battlefieldView[9][9])
{
    char line, column;
    
    GetCoordinates(&line, &column);
    switch(battlefieldAttecked[line][column])
    {
        case '0':
            battlefieldView[line][column] = 'M';
            printf("Fallo!\n\r");
            break;
        case 'S':
            battlefieldView[line][column] = 'H';
            printf("Acerto!\n\r");
            break;
        default:
            printf("Ya atacaste ahi!\n\r");
            break;
    }
    ShowBatttleField(battlefieldView);
}

// Valida si el juego ya termino en caso de ser cierto se imprime el ganador.
bool IsGameOver(char battlefield1[9][9], char battlefield2[9][9])
{
    char hits1 = 0, hits2 = 0;
    for (int i = 0; i<9; i++)
    {
        for (int n = 0; n<9; n++)
        {
            if (battlefield1[i][n] == 'H')
            {
                hits1++;
            }
            if (battlefield2[i][n] == 'H')
            {
                hits2++;
            }
            if (hits1 == 9 && hits2 == 9)
            {
                printf("Empate!\n\r");
                return true;
            }
            if (hits1 == 9)
            {
                printf("Jugador 1 gano!\n\r");
                return true;
            }
            if (hits2 == 9)
            {
                printf("Jugador 2 gano!\n\r");
                return true;
            }
        }
    }
    return false;
}

// Jugar un jugador vs otro.
void Game1v1()
{
    char player1Battlefield[9][9];
    char player2Battlefield[9][9];
    InitBattleShip(player1Battlefield);
    InitBattleShip(player2Battlefield);
    printf("Jugador uno pon tus barcos.\n\r");
    InitPlayerBattleShip(player1Battlefield);
    printf("Haga click y pase la computadora al otro jugador.\n\r");
    getchar();
    system("clear");
    printf("Jugador dos pon tus barcos.\n\r");
    InitPlayerBattleShip(player2Battlefield);
    printf("Haga click y pase la computadora al otro jugador.\n\r");
    getchar();
    system("clear");
    char player1View[9][9];
    char player2View[9][9];
    InitBattleShip(player1View);
    InitBattleShip(player2View);
    while (!IsGameOver(player1View, player2View))
    {
        printf("Jugador 1 ataca!\n\r");
        Attack(player2Battlefield, player1View);
        printf("Haga click y pase la computadora al otro jugador.\n\r");
        getchar();  
        system("clear");
        printf("Jugador 2 ataca!\n\r");
        Attack(player1Battlefield, player2View);
        printf("Haga click y pase la computadora al otro jugador.\n\r");
        getchar(); 
        system("clear");
    }

    return;
}

// Randomisa un campo de batalla.
void InitRandomBattlefield(char array[9][9])
{
    char shipCount = 0;
    while (shipCount < 3)
    {
        char line = rand() % 9;  
        char column = rand() % 9;  
        char orientation = rand() % 4 + 1;
        if (IsValidCoordPosition(column, line, array, 3, orientation))
        {
            InsertShip(array, column, line, 3, orientation);
            shipCount ++;    
            ShowBatttleField(array);
        }
    }
    //ShowBatttleField(array);
}

// Ataca aleatoriamente.
void RandomAttack(char view[9][9], char attacked[9][9])
{
        char line = rand() % 9;  
        char column = rand() % 9;  
        switch(attacked[line][column])
        {
            case '0':
                view[line][column] = 'M';
                printf("La computadora fallo!\n\r");
                break;
            case 'S':
                view[line][column] = 'H';
                printf("La computadora acerto!\n\r");
                break;
            default:
                break;
        };
        printf("Vista de computadora:\n\r");
        ShowBatttleField(view);
}

// Juega contra una computadora.
void Game1vIA()
{
    char playerBattlefield[9][9];
    char playerAIBattlefield[9][9];
    InitBattleShip(playerBattlefield);
    InitBattleShip(playerAIBattlefield);
    printf("Jugador uno pon tus barcos.\n\r");
    InitPlayerBattleShip(playerBattlefield);
    printf("De click para continuar...");
    getchar();
    system("clear");
    printf("Jugador dos esta poniendo sus barcos.\n\r");
    InitRandomBattlefield(playerAIBattlefield);
    printf("De click para continuar...\n\r");
    getchar();
    system("clear");
    char player1View[9][9];
    char playerAIView[9][9];
    InitBattleShip(player1View);
    InitBattleShip(playerAIView);
    while (!IsGameOver(player1View, playerAIView))
    {
        printf("Jugador 1 ataca!\n\r");
        Attack(playerAIBattlefield, player1View);
        printf("Click para continuar...\n\r");
        getchar();  
        system("clear");
        printf("Jugador 2 esta atacando!\n\r");
        RandomAttack(playerAIView, playerBattlefield);
        printf("Click para continuar...\n\r");
        getchar(); 
        system("clear");
    }

    return;
}


int main ()
{
    srand(time(NULL));
    system("clear");
    char insertVal;
    while (insertVal != '3')
    {
        printf("Que quieres jugar?\n\r1-Mulijugador\n\r2-Solo\n\r3-Salir\r\n");
        insertVal = getchar();
        system("clear");
        switch (insertVal)
        {
            case '1':
                Game1v1();
                break;
            case '2':
                Game1vIA();
                break;
            default:
                break;
        }
    }
    
    return 0;
}










