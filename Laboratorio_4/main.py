#from threading import *
import threading
import time
import random
import logging
from clases import *
from datetime import datetime, timedelta

##################################################  SECCIÓN DE FUNCIONES  ####################################################
last_action = datetime.now()

def en_deadlock():
    global last_action
    if datetime.now() - last_action > timedelta(seconds=10):
        return True
    return False

def actualizar_tiempo():
    global last_action
    last_action = datetime.now()
'''


recorrer_isla(nombre_isla, pirata, num_isla)

Es una función que se encarga de identificar en qué tiempo el parámetro pirata (hebra) entra en la cola/puente esperando para entrar
en la isla, una vez esto suceda se toma el tiempo en que el pirata entra a la isla.
Los tiempos se escriben en el archivo correspondiente a la isla.

PARAMETROS:   nombre_isla: nombre isla   //   pirata = num pirata   // num_isla = si es la 1ra o 2da
RETORNO:      Se retorna el tiempo de entrada al puente de la isla para uso posterior.
'''
def recorrer_isla (nombre_isla, pirata, num_isla):
    isla = islas[nombre_isla]
    puente = isla["contador_max_puente"]
    isla_cant = isla["semaforo_isla"]
    timer = isla["duracion"]
    contador = isla["contador"]
    contador2 = isla["contador2"]
    limite = isla["capacidad"]
    #condition = isla["condicion"]
    logger = isla["logger"]

    puente.acquire() #entrada al puente
    entrada_puente = datetime.now().strftime("%H:%M:%S.%f") #registrar ingreso puente
    contador.incrementar() #contador de piratas en el puente

    isla_cant.acquire() #contador de piratas en la isla

    actualizar_tiempo()

    #contador capacidad isla
    while contador.value() < limite and not en_deadlock():
        time.sleep(0.01)

    contador2.incrementar() #1
    if contador2.value() == contador.value():
        contador.resetear()
        contador2.resetear()

    entrada_isla = datetime.now().strftime("%H:%M:%S.%f")
    puente.release()

    logger.info(f"Pirata {pirata}, {entrada_puente}, {entrada_isla}, {num_isla}")
    time.sleep(timer)
    isla_cant.release()

    return entrada_puente

'''
Bar_del_oraculo(pirata, islas_recorrer)

Es una función que se encarga de identificar el tiempo de entrada de un pirata al Bar y de mandarlos a recorrer las islas,
por último se encarga de registrar el tiempo de salida dedl pirata del Bar.
Se encarga de la escritura de los archivos "Bar_del_oraculo.txt" y "Salida.txt"

PARAMETROS:   pirata = id_pirata    islas_recorrer = 2 islas aleatorias
RETORNO:      No se retorna nada
'''
def Bar_del_oraculo(pirata,islas_recorrer):
    entrada_bar = datetime.now().strftime("%H:%M:%S.%f")
    tiempos_puentes = []
    n_isla = 0

    islas_recorrer = random.sample(islas_recorrer, 2)
    #print("Al pirata ", pirata , " se le asignaron las islas: ", islas_recorrer )

    for isla in islas_recorrer:
        n_isla += 1
        tiempos_puentes.append(recorrer_isla(isla, pirata, n_isla))

    with lock_bar:
        bar_logger.info(f"Pirata {pirata}, {entrada_bar}, {islas_recorrer[0]}, {tiempos_puentes[0]}, {islas_recorrer[1]}, {tiempos_puentes[1]}")

    salida_bar = datetime.now().strftime("%H:%M:%S.%f")
    with lock_salida:
        salida_logger.info(f"Pirata {pirata}, {salida_bar}")


##################################################  SECCIÓN MAIN  ####################################################

####  DATOS ENUNCIADO ####
islas = {
    "Isla de las Sombras":       {"capacidad": 10, "capacidad_puente": 20, "duracion": 9, "logger": logging.getLogger('Isla_de_las_Sombras')       },
    "Isla del Dragon Rojo":      {"capacidad": 2,  "capacidad_puente": 8,  "duracion": 5, "logger": logging.getLogger('Isla_del_Dragon_Rojo')      },
    "Isla de las Estrellas":     {"capacidad": 5,  "capacidad_puente": 15, "duracion": 7, "logger": logging.getLogger('Isla_de_las_Estrellas')     },
    "Isla del Bosque Encantado": {"capacidad": 3,  "capacidad_puente": 6,  "duracion": 4, "logger": logging.getLogger('Isla_del_Bosque_Encantado') },
    "Isla de los Susurros":      {"capacidad": 5,  "capacidad_puente": 6,  "duracion": 1, "logger": logging.getLogger('Isla_de_los_Susurros')      },
    "Isla del Trueno":           {"capacidad": 4,  "capacidad_puente": 9,  "duracion": 4, "logger": logging.getLogger('Isla_del_Trueno')           },
    "Isla del Tesoro Oculto":    {"capacidad": 2,  "capacidad_puente": 7,  "duracion": 5, "logger": logging.getLogger('Isla_del_Tesoro_Oculto')    },
}

totalPiratas = 500 # 500


####  INICIACIÓN DE LOGGERS  ###

#  ARCHIVOS
logging.basicConfig(level=logging.INFO, format='%(message)s')

bar_logger  = logging.getLogger('BarOraculo')
bar_handler = logging.FileHandler('BarOraculo.txt')
bar_logger.addHandler(bar_handler)

salida_logger  = logging.getLogger('Salida')
salida_handler = logging.FileHandler('Salida.txt')
salida_logger.addHandler(salida_handler)

#  ISLAS
for island_name, island in islas.items():
    handler = logging.FileHandler(f"{island_name.replace(' ', '_')}.txt")
    island["logger"].addHandler(handler)


####  CREACIÓN DE SEMÁFOROS, CANDADOS Y CONTADORES  ####
for isla in islas.values():
    capacidad_puente = isla["capacidad_puente"]
    capacidad_isla   = isla["capacidad"]
    isla["contador_max_puente"] = semaforos(capacidad_puente)
    isla["semaforo_isla"] = semaforos(capacidad_isla)
    isla["contador"] = contadorSeguro()
    isla["candado"] = Lock()
    #isla["condicion"] = Condition()
    isla["contador2"] = contadorSeguro()

lock_bar = Lock()
lock_salida =Lock()

####  INICIO SIMULACIÓN  ####
lista_islas = list(islas.keys())

piratas = []   #Creacion lista de hebras donde están los piratas

#Asignación aleatoria de islas
for i in range(totalPiratas):
    piratas.append(threading.Thread(target = Bar_del_oraculo, args = (i, lista_islas)))

for hebra in piratas:
    hebra.start()       # Iniciar cada hebra de pirata

for hebra in piratas:
    hebra.join()        # Esperar a que todos los hilos de piratas terminen

####  CIERRE DE LOS MANEJADORES DE LOGGING  ####
bar_handler.close()
salida_handler.close()
for island in islas:
    for handler in islas[island]["logger"].handlers:
        handler.close()
