# unimake (Universal makefile)

Универсальный Makefile, предназначен для сборки простейших проектов, состоящих из множества С/С++ файлов.
Возможно создание из одного набора исходных кодов нескольких бинарных результатов сборки с различными опциями компиляции.
Возможно указывать опции сборки и линковки прямо в исходном коде. При этом опции линковки `LDFLAGS` указанные в разных С/С++ файлах суммируются при линковке.
Есть функция рекурсивного обхода вложенных папок, содержащих `Makefile` с выполнением доступных целей.

Минимальные требования: GNU Make, GCC. 
Разместить исходные `Makefile` и `unimakefile.mki` в директории с исходными кодами и выполнить команду make. В качестве имени собранного приложения, будет использовано имя текущей директории. Если файл `unimakefile.mki` разместить в `/usr/local/include/` его не придётся копировать в каждый проект.

# Опции

bins-t - список целей, имена бинарных файлов.  
имя_цели-srcs - список файлов *.c и *.cpp   
имя_цели-ccflags_add -  флаги компилятора для указанной цели   
имя_цели-ldflags_add -  флаги линковщика для указанной цели   
имя_файла_с_расширением-ccflags_add - дополнительные флаги компилятора для казанного файла   
имя_файла_с_расширением-ccflags_exc - если будут указаны флаги компилятора, будут применяться только эти флаги.    

# Расширения

Часть опций можно хранить в исходном коде, например: -O2:-Wall:-std=c99    
для этого в исходном Си коде следует добавить следующие строки:    
```
#ifdef MAKE_GET_FLAGS
#error CCFLAGS:-O2:-Wall:-std=c99
#error LDFLAGS:-lm
#endif
```
Указанные флаги, в процессе сборки, будут добавлены к флагам, заданным в Makefile.   

# Примеры:

1.  
Требуется собрать два приложения с различными опциями компиляции и линковки, используя один общий файл.
В данном случае Makefile будет выглядеть следующим образом:
```
bins-t += app1 app2   

app1-srcs += file1.c file_share.c   
app1-ccflags_add := -O2  
app1-ldflags_add := -lm  
file_share.c-ccflags_exc := -s -O3 r -Wall -std=c99  

app2-srcs += file2.c file_share.c  
app1-ccflags_add := -O1  
app1-ldflags_add := -lrt  
file2.c-ccflags_add := -Wall  
```

2.  
По умолчанию всего две рекурсивные цели `all` и `clean`.   
Для добавления ещё одной цели, например, `test`, во всё дерево проекта, можно использовать конструкцию со следующим содержимым Makefile:   
```
test: start_message dirs_targets end_message
	@echo TEST
	@:
```
 назовите его, например, addtarget.mki и разместите в любом месте проекта, можно в отдельной папке или в `/usr/local/include/`.
Добавтье в `Makefile` находящийся в корне проекта строку `export GD_INCLUDE_MAKEFILES := /абсолютный_путь/addtarget.mki`.
Это заставит включать данный файл при рекурсивном вызове, и указанная цель появиться во всём дереве проекта.
Для выполнения уникальных действий для цели, в какой-либо папке создайте в соответствующем `Makefile` цель и задайте необходимые действия.   
   

3.  
Если требуется включить сборку проекта исходные коды находящиеся во вложенной(ых) папке(ах), в Makefile необходиом это описать явно:   
```
bins-t += app
# указать наборы файлов
app-srcs += $(wildcard *.c) $(wildcard src/*.c)
# либо указать отдельные файлы
app-srcs += app/file.c
```
В даном случае дерево объектных файлов, будет повторять дерево исходных кодов.   
PS: одинаковые имена для c и cpp находящихся в одной папке не допускаются.   
   
