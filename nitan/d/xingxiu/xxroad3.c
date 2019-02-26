// Room: /d/xingxiu/xxroad3.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;

void create()
{
        set("short", "六盤山");
        set("long", @LONG
這是一座不太高的小山。山頂望去，瓦藍的天空 (sky)飄着幾朵淡
淡的白雲。一羣大雁發出「嘎嘎」的叫聲，從頭上飛過。西面山下長城
的殘垣斷壁依稀可辨。長城的盡頭是一座雄偉的關隘。路旁有一處懸崖
之上刻着首詞(poem)。
LONG );
        set("exits", ([
                "westdown"  : __DIR__"jiayuguan",
                "northdown" : "/d/yongdeng/yongdeng",
                "southdown" : __DIR__"xxroad2",
        ]));

        set("item_desc", ([ 
"poem" : "崖壁上刻着一首清平樂：

  何  今  紅  六  屈  不  望  天
  時  日  旗  盤  指  到  斷  高
  縛  長  漫  山  行  長  南  雲
  得  纓  卷  上  程  城  飛  淡
  蒼  在  西  高  二  非  雁  
  龍  手  風  峯  萬  好  
                      漢

你現在是好漢了！
\n",
"sky" : "
                              \\/             \\/
                   /*=*         \\/       \\/
                   (*=*=)         \\/  \\/
               {/*=**=/            \\/
                         __
                        /\\.\\_   
               /\\  /\\  /  ...\\   /\\
              / .\\/ .\\/    .. \\_/ .\\
             /  ..\\  /    ... . \\  .\\      /\\
            /凸凸凸\\/凸凸凸. ..凸\\凸.\\    / .\\  
  _凸凸凸凸/     ..凸     凸凸凸..\\__.\\凸/  ..\\_凸凸凸凸凸凸凸凸凸凸凸凸_\n\n"
]));

        set("no_clean_up", 0);
        set("outdoors", "silu");

        set("coor/x", -9600);
        set("coor/y", 3000);
        set("coor/z", 60);
        setup();
        replace_program(ROOM);
}