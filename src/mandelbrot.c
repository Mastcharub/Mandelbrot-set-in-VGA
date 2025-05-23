typedef unsigned char ui8;
typedef unsigned short ui16;
typedef unsigned int ui32;

#define WIDTH                       320
#define HEIGHT                      200
#define VGA             (ui8 *) 0xA0000

void plot(ui16 x, ui16 y, ui8 col);
void mandelbrot(float zoom, float move_X, float move_Y);

// Entry point of the 'kernel'
extern void kmain(){
    mandelbrot(1, -0.5, 0); // respectevely: zoom multiplier and x and y coordinates of the view
}

void plot(ui16 x, ui16 y, ui8 col){
    ui32 offset = (ui32) (y * WIDTH + x);
    *(VGA + offset) = col;
} 

void mandelbrot(float zoom, float move_X, float move_Y){
    float p_Re, p_Im;                               // real and imaginary part of the pixel p
    float new_z_Re, new_z_Im, old_z_Re, old_z_Im;   // real and imaginary parts of new and old z
    int maxIterations = 300;

    for(ui16 y = 0; x < HEIGHT; y++){
        for(ui16 x = 0; x < WIDTH; x++){

            // Calculate the initial real and imaginary value, based on the pixel location and zoom and position values
            p_Re = 1.5 * (x - WIDTH / 2) / (0.5 * zoom * WIDTH) + move_X;
            p_Im = (y - HEIGHT / 2) / (0.5 * zoom * HEIGHT) + move_Y;
            new_z_Re = new_z_Im = old_z_Re = old_z_Im = 0; // start at (0;0)

            // Start the iteration process
            ui16 i;
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
