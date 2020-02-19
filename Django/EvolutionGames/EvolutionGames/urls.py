from django.conf.urls import patterns, include, url
from django.contrib import admin
from django.conf import settings
from principal import views
from django.views.generic import TemplateView
from django.contrib.staticfiles.urls import staticfiles_urlpatterns
from django.conf.urls.static import static
from principal.views import BuscarView

urlpatterns = patterns('',
	# Examples:
	# url(r'^$', 'EvolutionGames.views.home', name='home'),
	# url(r'^blog/', include('blog.urls')),

	url(r'^admin/', include(admin.site.urls)),
	url(r'^media/(?P<path>.*)$','django.views.static.serve',{'document_root':settings.MEDIA_ROOT}),
	url(r'^buscar/$', BuscarView.as_view(), name='buscar'),
)

urlpatterns += patterns('principal.views',
	# Examples:
	# url(r'^$', 'EvolutionGames.views.home', name='home'),
	# url(r'^blog/', include('blog.urls')),

	
	url(r'^$','inicio'),
	url(r'^juegos/$','lista_juegos'),
	url(r'^juego/(?P<pk>\d+)/','detalle_juego'),
	url(r'^juego/nuevo/$','nuevo_juego'),
	url(r'^usuario/nuevo/$','nuevo_usuario'),
	url(r'^ingresar/$','ingresar'),
	url(r'^privado/$','privado'),
	url(r'^cerrar/$', 'cerrar'),
	url(r'^juego/editar/(?P<id_juego>\d+)/$','editar_juego'),
	url(r'^juego/eliminar/(?P<id_juego>\d+)/$','eliminar_juego'),
	url(r'^perfil/(?P<id_usuario>\d+)/$','mi_perfil'),
	url(r"^poncomentario/(\d+)/$","poncomentario"),
	url(r'^perfil/(?P<id_usuario>\d+)/subir/$','nuevo_juego'),
	url(r"^misjuegos/(?P<id_usuario>\d+)/$","mis_juegos"),
) 