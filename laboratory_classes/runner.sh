#! /usr/bin/bash


        args=("$@")

        if [ "$args" = "b" ] 
        then
                echo "build"
                cmake -B build -H.
                cmake --build build --target all
        elif [ "$args" = "p" ] 
        then
                openocd -f board/stm32f4discovery.cfg  -c "program build/BareRTOS.elf verify reset exit"
        elif [ "$args" = "r" ] 
        then
                cmake -B build -H.
                cmake --build build  --target all
                openocd -f board/stm32f4discovery.cfg  -c "program build/BareRTOS.elf verify reset exit"
        else
                echo "failed"
        fi

        exit 0
