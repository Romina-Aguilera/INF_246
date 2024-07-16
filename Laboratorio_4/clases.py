from threading import Condition, Lock

##################################################  CLASES UTILIZADAS  ####################################################
'''
class contadorSeguro, es una clase que se encarga de trabajar los candados utilizados en el main
también asegura la seguridad en el uso de los candados.
'''
# Este comentario y el de abajo lo puedes borrar, el tema es que no estoy tan segura de lo que describí
#Contador que se encarga de verificar el num de piratas(?)
class contadorSeguro:
    #  CONSTRUCTOR
    def __init__(self, valor = 0):
        self._counter = valor
        self._lock = Lock()

    #  MÉTODOS
    def value(self):
        with self._lock:
            return self._counter

    def incrementar(self):
        with self._lock:
            self._counter += 1

    def disminuir(self):
        with self._lock:
            self._counter -= 1

    def resetear(self):
        with self._lock:
            self._counter = 0

'''
class semaforos, es una clase que se encarga de implementar los semáforos y definir operaciones útiles para estos,
además de asegurar la seguridad en el uso de los mismos.
'''
class semaforos:
    #  CONSTRUCTOR
    def __init__(self, value = 1):
        if value < 0:
            raise ValueError("semaphore initial value must be >= 0")
        self._lock  = Lock()
        self._value = value
        self._lista = []

    #  MÉTODOS
    # acquire y release controlan el orden
    def acquire(self):
        with self._lock:
            if self._value == 0:
                cond = Condition(self._lock)
                self._lista.insert(0,cond)
                cond.wait()
            self._value -= 1

    __enter__ = acquire

    def release(self):
        with self._lock:
            self._value += 1
            if len(self._lista) > 0:
                self._lista.pop().notify()

    def __exit__(self, t, v, tb):
        self.release()
