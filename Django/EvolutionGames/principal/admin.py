from django.contrib import admin

# Register your models here.

from principal.models import Juego, Palabra_Clave, Comentario

admin.site.register(Juego)
admin.site.register(Comentario)
admin.site.register(Palabra_Clave)