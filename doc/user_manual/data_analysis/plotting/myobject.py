import numpy

class myObject(object):
  def _plot_(self, options):
    PI = numpy.pi
    xdata = numpy.arange(-PI,PI,0.1)
    ydata1 = numpy.cos(xdata)
    ydata2 = numpy.sin(xdata)
    return( [
              {'Type' : "XY", 'xdata':xdata, 'ydata':ydata1, 'label':'Cos'},
              {'Type' : "XY", 'xdata':xdata, 'ydata':ydata2, 'label':'Sin'}
            ] )

X = myObject()

from pytriqs.Base.Plot.MatplotlibInterface import oplot
oplot(X,'-o')
