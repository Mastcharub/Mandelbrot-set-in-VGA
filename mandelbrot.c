typedef unsigned char ui8;
typedef unsigned short ui16;
typedef unsigned int ui32;

#define WIDTH                       320
#define HEIGHT                      200
#define VGA             (ui8 *) 0xA0000

void plot(ui16 x, ui16 y, ui8 col);
void mandelbrot();

// Entry point of the 'kernel'
extern void kmain(){
    mandelbrot();
}

void plot(ui16 x, ui16 y, ui8 col){
    ui32 offset = (ui32) (y * WIDTH + x);
    *(VGA + offset) = col;
}

void mandelbrot(){
    float p_Re, p_Im;                               // real and imaginary part of the pixel p
    float new_z_Re, new_z_Im, old_z_Re, old_z_Im;   // real and imaginary parts of new and old z
    float zoom = 1, move_X = -0.5, move_Y = 0;      // change these to zoom and change position
    int maxIterations = 300;

    for(int y = 0; y < HEIGHT; y++){
        for(int x = 0; x < WIDTH; x++){

            // Calculate the initial real and imaginary value, based on the pixel location and zoom and position values
            p_Re = 1.5 * (x - 320 / 2) / (0.5 * zoom * 320) + move_X;
            p_Im = (y - 200 / 2) / (0.5 * zoom * 200) + move_Y;
            new_z_Re = new_z_Im = old_z_Re = old_z_Im = 0; // start at (0;0)

            // Start the iteration process
            int i;
            for(i = 0; i < maxIterations; i++){

                // Save old value
                old_z_Re = new_z_Re;
                old_z_Im = new_z_Im;

                // Real iteration
                new_z_Re = old_z_Re * old_z_Re - old_z_Im * old_z_Im + p_Re;

                // Immaginary iteration
                new_z_Im = 2 * old_z_Re * old_z_Im + p_Im;

                // Stops when the point is outside the circle of radius 2
                if((new_z_Re * new_z_Re + new_z_Im * new_z_Im) > 4) break;
            }

            // Pixels that escape quickly get darker colors (low i), and those that take longer to escape get brighter ones (high i).
            plot(x, y, (i * 255 / maxIterations));

            // A more minimal and simpler way of plotting the set
            /*
            if(i < maxIterations){
                plot(x, y, 2);
            }else{
                plot(x, y, 0);
            }
            */
        }
    }
}
