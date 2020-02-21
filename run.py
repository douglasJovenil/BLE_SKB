from pynput.keyboard import Key, Controller
from time import sleep
from os import system, chdir
import subprocess
from argparse import ArgumentParser
import sys


def main():
    # Configura Parser
    parser = ArgumentParser(description='Serviços úteis ao se utilizar o SDK da Nordic')
    parser.add_argument('-p', '--path', help='Caminho do projeto a ser compilado', required=True)
    parser.add_argument('-c', '--compile', action='store_true', help='Compila o firmware')
    parser.add_argument('-b', '--burn', action='store_true', help='Grava o firmware')
    parser.add_argument('-e', '--erase', action='store_true', help='Apaga a memória')
    parser.add_argument('-s', '--soft', help='Grava o softdevice, deve ser passado como parametro o nome do arquivo que se encontra na pasta hex')

    #Verfica se argumentos forma passados pelo terminal
    if (len(sys.argv) <= 2):
        parser.print_help()
        exit(0)
    
    # Filtra informacoes recebidas pelo parser
    args = parser.parse_args()
    
    # Limpa o terminal
    system('clear')

    # Inicia a lista de comandos no JLink Commander
    commands = ['JLinkExe',
                'device NRF52840_XXAA',
                'si SWD',
                'speed 4000',
                'connect']
    
    # Função para adicionar comandos na lista de comandos
    addCommand = lambda cmd: commands.append(cmd)

    # Função para verificar se deve executar os comandos para sair do JLink Commander
    canAddExitCommands = lambda: args.burn or args.erase or args.soft

    # Processo de compilação
    if (args.compile):
        # Muda de diretorio, execute make e aguarda a finalizacao
        chdir(f'{args.path}/pca10056/s140/armgcc')
        make = subprocess.Popen('make')
        make.wait()

        # Se houverem problemas, parar o programa
        if (subprocess.check_call('make') != 0):
            exit(0)

    # Processo de apagar memória
    if (args.erase):
        addCommand('erase')
    
    if (args.soft):
        chdir(f'{args.path}/hex')
        addCommand(f'loadfile {args.path}/{args.soft}')

    # Processo de gravação
    if (args.burn):
        addCommand('loadfile ./_build/nrf52840_xxaa.hex')
    
    # Adiciona comandos para sair do JLinkCommander e executa todos os comandos
    if (canAddExitCommands()):
        addCommand('r')
        addCommand('g')
        addCommand('q')
        addCommand('exit')
        executeCommands(commands)


# Função para executar todos os comandos
def executeCommands(commands):
    # Objeto para controlar o teclado
    keyboard = Controller_d()

    # Abre um novo terminal para evitar que comandos fiquem no historico
    system('gnome-terminal')
    sleep(0.2)

    # Executa os comandos
    for cmd in commands: 
        keyboard.type_and_enter(cmd)


class Controller_d(Controller):
    def __init__(self):
        Controller.__init__(self)

    def press_and_release(self, key):
        self.press(key)
        self.release(key)
    
    def type_and_enter(self, msg):
        self.type(msg)
        self.press_and_release(Key.enter)
        sleep(0.05)
    
if __name__ == '__main__':
    main()