koka3D is a software rasterizer I wrote to better understand the 3D graphics pipeline.  
This project required me to understand applications of data structures, linear algebra, data-stream interpretation, input handling, and more.  

My own library handles parsing, matrices, transformation, uv application, and sorting. SFML handles input and the window context.

<img src="meta/chair.png" alt="Image of chair" width="250"/> <img src="meta/laika.png" alt="Image of laika" width="250"/>

Features: 
- Load any model through OBJ Parsing.  
- Load any texture to any model.  
- Controls to transform the model.  
- Frame time performance metrics

Usage: 
- Open the binary through the executable  
- Input a model located in assets/model/  
- Input a texture located in texture/

Dependencies:  
- SFML 2.6.2

Credits:
- "laika" created by Laika.
- Other models and textures are original.  
- SFML 2.6.2 licensed under zlib