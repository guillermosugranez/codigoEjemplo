# -*- encoding: utf-8 -*-

from django.forms import ModelForm
from django import forms
from principal.models import Juego, Palabra_Clave, Comentario

class JuegoForm(ModelForm):
	class Meta:
		model = Juego
		exclude = ['usuario', 'estrellas']
		
class Palabra_ClaveForm(ModelForm):
	class Meta:
		model = Palabra_Clave

class ComentarioForm(ModelForm):
	class Meta:
		model = Comentario
		exclude = ['juego']

