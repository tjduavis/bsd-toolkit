''
' Part 3 - Abstract Factory pattern (p. 87)
''

Public Class Client
    Dim wFactory As WidgetFactory
    Dim windowType As Window
    Dim scrollbartype As ScrollBar
End Class

Interface WidgetFactory
    Function CreateScrollBar() As ScrollBar
    Function CreateWindow() As Window
End Interface

Public Class MotifWidgetFacotry
    Implements WidgetFactory
    Function CreateScrollBar() As ScrollBar Implements WidgetFactory.CreateScrollBar
        Dim scrollBar As Object
        Return scrollBar
    End Function
    Function CreateWindow() As Window Implements WidgetFactory.CreateWindow
        Dim window As Object
        Return window
    End Function
End Class

Public Class PMWidgetFacotry
    Implements WidgetFactory
    Function CreateScrollBar() As ScrollBar Implements WidgetFactory.CreateScrollBar
        Dim scrollBar As Object
        Return scrollBar
    End Function
    Function CreateWindow() As Window Implements WidgetFactory.CreateWindow
        Dim window As Object
        Return window
    End Function
End Class

Public MustInherit Class Window
End Class

Public Class PMWindow
    Inherits Window
End Class

Public Class MotifWindow
    Inherits Window
End Class

Public Class ScrollBar
End Class

Public Class PMScrollBar
    Inherits ScrollBar
End Class

Public Class MotifScrollBar
    Inherits ScrollBar
End Class