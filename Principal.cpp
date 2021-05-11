#include <iostream>
#include <cstdlib>
#include <cstring>
#include <math.h>
#include <sys/types.h>
#include <dirent.h>
#include <list>
#include <iterator>
#include <stdio.h>
#include <string.h>
#include <fstream>
// Librerías de OpenCV

//#include <opencv2/opencv.hpp>

#include <opencv2/core/core.hpp> // Contiene los elementos base de OpenCV (matrices, arreglos, etc.)
#include <opencv2/highgui/highgui.hpp> // Contiene estructuras para crear la interfaz gráfica
#include <opencv2/imgproc/imgproc.hpp> // Procesamiento de imágenes
#include <opencv2/imgcodecs/imgcodecs.hpp> // Códecs para leer determinados formatos de imágenes
#include <opencv2/video/video.hpp> // Procesamiento y escritura
#include <opencv2/videoio/videoio.hpp> // de video

using namespace std;
using namespace cv; // El espacio de nombres donde están definidas algunas funciones de OpenCV

int centro = 0;


Mat frame; // 30 fps = 30 frames per second (30 imágenes por segundo)
Mat imagenGenerada;

void funcionTrackbar(int v, void *data){
    
    if (centro == 0)
    {
        imagenGenerada = frame;
        imshow("imagenGenerada", imagenGenerada);
    }
    if (centro == 1)
    {
        cvtColor(frame, imagenGenerada, COLOR_BGR2GRAY);
        imshow("imagenGenerada", imagenGenerada);
    }
    if (centro == 2)
    {
        cvtColor(frame, imagenGenerada, COLOR_BGR2HSV);
        imshow("imagenGenerada", imagenGenerada);

    }
    if (centro == 3)
    {
        cvtColor(frame, imagenGenerada, COLOR_BGR2Lab);
        imshow("imagenGenerada", imagenGenerada);
    }
    if (centro == 4)
    {
         cvtColor(frame, imagenGenerada, COLOR_BGR2YCrCb);
        imshow("imagenGenerada", imagenGenerada);
    }
}

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
     if  ( event == EVENT_LBUTTONDOWN )
     {
          cout << "La imagen a sido guardada en este directorio"<< endl;
          imwrite("Imagen-CapturadaConMouse.jpg", imagenGenerada);
     }
}
    
    
   

int main(int argc, char *argv[]){
    
    VideoCapture video(0);

    if(video.isOpened()){

        namedWindow("Video Original", WINDOW_AUTOSIZE);
        namedWindow("imagenGenerada", WINDOW_AUTOSIZE);
        createTrackbar("0.RGB, 1.Gray, 2.HSV, 3.LAB, 4.YCrCb","Video Original",&centro, 4, funcionTrackbar, NULL);

        while(3==3){
            video >> frame;
            
            if(frame.rows==0 || frame.cols==0){
                cout << "Acabó el vídeo..." << endl;
                break;
            }
            
            resize(frame, frame, Size(), 1, 1);
            imshow("Video Original", frame);
            
            
            //Obtener informacion del mouse 
            setMouseCallback("imagenGenerada", CallBackFunc, NULL);

            if(waitKey(23)==27){
                break;
            }
        }
        video.release();
    }

    destroyAllWindows(); // Cierra todas las ventanas que se hayan creado en el programa

    return 0;
}





