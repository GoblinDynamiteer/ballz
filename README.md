#SDL Ballz

## Build

```bash
cmake -S . -B build
cmake --build build
./build/ballz
```

Window size defaults to `1920x1080` and can be overridden at configure time:

```bash
cmake -S . -B build -DWINDOW_WIDTH=1280 -DWINDOW_HEIGHT=720
```

## Linting

```bash
cmake --build build --target format
cmake --build build --target format-check
cmake --build build --target lint
```

---

*SDL / Geometry practice.* 

A simple game / demo, with different modes.  

Left / Right mouse button adds balls.  
Scrolling the wheel cycles through modes: Create balls, repel, magnet.  


[YouTube demo 1](https://www.youtube.com/watch?v=ErFAqmyj5XM)  
[YouTube demo 2](https://www.youtube.com/watch?v=TusFuPc4rq8)


---

**Screenshots**   
![Ballz 005](https://github.com/GoblinDynamiteer/ballz/blob/master/img/balls_005.png)  
![Ballz 006](https://github.com/GoblinDynamiteer/ballz/blob/master/img/balls_006.png)  
![Ballz 008](https://github.com/GoblinDynamiteer/ballz/blob/master/img/balls_008.png)  
![Ballz 009](https://github.com/GoblinDynamiteer/ballz/blob/master/img/balls_009.png)  
![Ballz 010](https://github.com/GoblinDynamiteer/ballz/blob/master/img/balls_010.png)  
