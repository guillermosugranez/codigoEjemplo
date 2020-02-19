# Modelos
from principal.models import Palabra_Clave, Juego, Comentario
# Formularios
from principal.forms import JuegoForm, Palabra_ClaveForm, ComentarioForm
from django.views.generic import TemplateView

from django.contrib.auth.models import User
from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render_to_response, get_object_or_404, render
from django.core.context_processors import csrf
from django.template import RequestContext
from django.core.mail import EmailMessage
from django.core.urlresolvers import reverse

from django.contrib.auth.forms import UserCreationForm, AuthenticationForm
from django.contrib.auth import login, authenticate, logout
from django.contrib.auth.decorators import login_required
# Create your views here.

def inicio(request):
	usuario = request.user
	return render_to_response('inicio.html',{'usuario': usuario}, context_instance=RequestContext(request))
	
def lista_juegos(request):
	usuario = request.user
	juegos = Juego.objects.all()
	return render_to_response('juegos.html',{'datos':juegos, 'usuario': usuario}, context_instance=RequestContext(request))

@login_required(login_url='/ingresar')
def mi_perfil(request, id_usuario):
	usuario = request.user
	return render_to_response('perfil.html',{'usuario': usuario}, context_instance=RequestContext(request))

def detalle_juego(request, pk):
	idjuego = Juego.objects.get(pk=int(pk)) # Aqui recoge el juego y define pk
	etiquetacion = idjuego.etiquetas.all()
	comentario = Comentario.objects.filter(juego = idjuego)
	d = dict(juego = idjuego, comentario = comentario, form=ComentarioForm(), usuario=request.user)
	d.update(csrf(request))

	return render_to_response('juego.html', d, context_instance=RequestContext(request))
	
@login_required(login_url='/ingresar')
def mis_juegos(request, id_usuario):
	usuario = request.user
	juegos = Juego.objects.filter(usuario=usuario)
	return render_to_response('MisJuegos.html',{'datos':juegos, 'usuario': usuario}, context_instance=RequestContext(request))
	
# =======	Formularios	=======

# JUEGO
@login_required(login_url='/ingresar')
def nuevo_juego(request, id_usuario):
	usuario=request.user
	if request.method=='POST':
		formulario = JuegoForm(request.POST, request.FILES)
		if formulario.is_valid():
			Juego=formulario.save(commit=False)
			Juego.usuario=request.user
			Juego.save()
			return HttpResponseRedirect('/juegos')
	else:
		data={'usuario':request.user.username}
		formulario = JuegoForm(initial=data)
	return render_to_response('juegoform.html',{'formulario':formulario, 'usuario':usuario}, context_instance=RequestContext(request))

# Palabra_Clave
@login_required(login_url='/ingresar')
def nuevo_Palabra_Clave(request):
	if request.method=='POST':
		formulario = Palabra_ClaveForm(request.POST)
		if formulario.is_valid():
			formulario.save()
			return HttpResponseRedirect('/juegos')
	else:
		formulario = Palabra_ClaveForm()
	return render_to_response('Palabra_Claveform.html',{'formulario':formulario}, context_instance=RequestContext(request))

# COMENTARIO
def poncomentario(request, pk):
	p = request.POST # aqui recojo lo que me ha enviado el request
	autor=request.user # aqui recojo quien ha enviado el request

	comentario = Comentario(juego = Juego.objects.get(pk=pk)) # Guardo todos los comentarios que han hecho sobre el juego
	cf = ComentarioForm(p, instance=comentario) # Creo el formulario pasandole p y los comentarios

	cf.fields['autor'].required=False # No requiero el campo autor en el formulario

	comentario = cf.save(commit=False)
	comentario.autor = autor # El usuario que hizo el request (pidio hacer un comentario) es el autor
	comentario.save()

	return HttpResponseRedirect (reverse("principal.views.detalle_juego", args=[pk]))

# =======	Gestion de usuarios	=======

def ingresar(request):
    if not request.user.is_anonymous():
        return HttpResponseRedirect('/privado')
    if request.method == 'POST':
        formulario = AuthenticationForm(request.POST)
        if formulario.is_valid:
            usuario = request.POST['username']
            clave = request.POST['password']
            acceso = authenticate(username=usuario, password=clave)
            if acceso is not None:
                if acceso.is_active:
                    login(request, acceso)
                    return HttpResponseRedirect('/privado')
                else:
                    return render_to_response('noactivo.html', context_instance=RequestContext(request))
            else:
                return render_to_response('nousuario.html', context_instance=RequestContext(request))
    else:
        formulario = AuthenticationForm()
    return render_to_response('ingresar.html',{'formulario':formulario}, context_instance=RequestContext(request))

def nuevo_usuario(request):
    if request.method=='POST':
        formulario = UserCreationForm(request.POST)
        if formulario.is_valid():
            formulario.save()
            return HttpResponseRedirect('/')
    else:
        formulario = UserCreationForm()
    return render_to_response('nuevousuario.html',{'formulario':formulario}, context_instance=RequestContext(request))

@login_required(login_url='/ingresar')
def privado(request):
    usuario = request.user
    return render_to_response('privado.html', {'usuario':usuario}, context_instance=RequestContext(request))

@login_required(login_url='/')
def cerrar(request):
    logout(request)
    return HttpResponseRedirect('/')

# =======	Editar	=======

# EDITAR JUEGO
# JUEGO
@login_required(login_url='/ingresar')
def editar_juego(request, id_juego):
	juego = Juego.objects.get(id=id_juego)
	if request.method=='POST':
		formulario = JuegoForm(request.POST, instance=juego)
		if formulario.is_valid():
			#lineas para que no aparezca en authentication
			formulario.save()
			return HttpResponseRedirect('/juegos')
	else:
		formulario = JuegoForm(instance=juego)
	return render_to_response('juegoform.html',{'formulario':formulario}, context_instance=RequestContext(request))

# =======	Eliminar	=======
# Eliminar JUEGO
def eliminar_juego(request, id_juego):
	juego=Juego.objects.get(id=comentario_id)
	return HttpResponseRedirect ("/")
	
# ============ BUSCAR ==============

class BuscarView(TemplateView):

	def post(self, request, *args, **kwargs):
		buscar = request.POST['buscalo'] # Lo que ha enviado el formulario es lo que guardo
		if buscar:
			palabrasClave = Palabra_Clave.objects.filter(nombre__contains=buscar) # busco "Palabras clave" donde aparezca la palabra que busco
			
			juegos = Juego.objects.all()
			datos = []
			for juego in juegos:
				etiquetas = juego.etiquetas.all()
				datos.append(dict([(juego,etiquetas)]))
			return render(request, 'buscar.html', {'palabrasClave':palabrasClave, 'datos':datos})
		else:
			return HttpResponseRedirect("/")