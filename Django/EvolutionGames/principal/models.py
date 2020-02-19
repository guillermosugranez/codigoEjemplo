from django.db import models
from django.contrib.auth.models import User

# Create your models here.

class Palabra_Clave(models.Model):
	nombre = models.TextField(max_length=100, unique=True)
	
	def __unicode__(self):
		return self.nombre

class Juego(models.Model):
	titulo = models.CharField(max_length=100, unique=True)
	descripcion = models.TextField()
	imagen = models.ImageField(upload_to='media/imagenes', verbose_name='Imagen', blank=True)
	tiempo_registro = models.DateTimeField(auto_now=True)
	usuario = models.ForeignKey(User, null=True, blank=True)
	etiquetas = models.ManyToManyField(Palabra_Clave, blank=True)
	enlace = models.URLField(blank=False)
	
	def __unicode__(self):
		return self.titulo

class Comentario(models.Model):
	tiempo_registro = models.DateField(auto_now=True)
	autor = models.ForeignKey(User, null=True, blank=True)
	juego = models.ForeignKey(Juego)
	texto = models.TextField(blank=False)
	
	def __unicode__(self):
		return ("%s %s" % (self.juego, self.texto[:60]))
		# Esto lo que haces es devolver el nombre del objeto creado