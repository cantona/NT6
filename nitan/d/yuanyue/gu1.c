// This program is a part of NITAN MudLIB

inherit ROOM;
#include <room.h>

void create()
{
        int i;
        object girl;
        set("short", "谷中");
        set("long", @LONG
溪流蜿蜒如帶，朱欄橫跨水上，幾只乳燕在花林中飛旋來去。草
坪上土墩間，斜坐著幾個披發少女，或披輕紗，或著柔袍，都在盈盈
淺笑，流眸低語。
LONG );
        set("exits", ([ /* sizeof() == 4 */
                "south" : __DIR__"gu0",
                "west" : __DIR__"gu2",
      
        ]));  
        set("objects", ([
                CLASS_D("mojiao/chunhua") : 1,
                CLASS_D("mojiao/qiuyue") : 1,
        ]) );
        set("outdoors","wansong");      
        set("coor/x",120);
        set("coor/y",10);
        set("coor/z",10);
        setup(); 
} 
