#!/bin/bash

cd /home/gleb/CXX/DialogBot2023/scripts
# Путь к файлу с PID (используем ../ для перехода на уровень выше)
pid_file="../files/PID.txt"

# Проверка наличия файла с PID
if [ -f "$pid_file" ]; then
	    # Считывание PID из файла
	        pid=$(cat "$pid_file")

		    # Проверка, существует ли процесс с указанным PID
		        if ps -p $pid > /dev/null; then
				        echo "Процесс с PID $pid уже запущен."
					    else
						            echo "Процесс с PID $pid не найден. Запускаю bot_start.sh..."
							            # Запуск скрипта bot_start.sh и перенаправление вывода в файл error_log.txt
								            ./bot_start.sh >>../temp/log.txt 2>&1 &
									        fi
									else
										    echo "Файл с PID не найден. Необходимо сначала создать файл pid.txt с указанным PID."
fi

