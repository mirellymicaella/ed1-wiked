#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Editor.h"

struct editor{
    char* nome;
};

Editor* CriaEditor(char* nome){
    Editor* editor = (Editor*)malloc(sizeof(Editor));
    editor->nome = strdup(nome);
    return editor;
}

char* RecuperaNomeEditor (Editor* editor){
    return editor->nome;
}

void DestroiEditor(Editor* editor){
    if(editor!=NULL){
        free(editor->nome);
        free(editor);
    }
}