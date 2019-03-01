// This program is a part of NITAN MudLIB

inherit ROOM;
#include <room.h>

void create()
{
        set("short", "小徑");
        set("long", @LONG
一條五色彩石小徑直通精舍，兩旁種滿鮮花，五彩繽紛。路邊更
有各種果樹，果(yiguo)已熟透,甚為誘人。一扇玉門在陽光下份外可
愛。
LONG );
        set("exits", ([ /* sizeof() == 4 */
                "eastup" : __DIR__"gu3",
                "westdown" : __DIR__"gu5",
 
        ]));
        set("outdoors","tieflag");      
        create_door("westdown","玉門","eastup",DOOR_CLOSED);         
        set("coor/x",90);
        set("coor/y",10);
        set("coor/z",-10);
        setup(); 
}
void init()
{
        add_action("do_get","pick");
}          
int do_get(string arg)
{
        object swo;
        if( query("mark/been_get")>10) return notify_fail("果子已被摘光了。\n");
        if(random(1000)>10) 
        { 
                swo=new(__DIR__"obj/yiguo");
                swo->move(this_player());
                addn("mark/been_get",1);
                write("你從樹上摘了一個果子。\n" );
        }
        else
        { 
                swo=new(__DIR__"obj/yiguo1");
                swo->move(this_player());
                addn("mark/been_get",1);
                write("你從樹上摘了一個果子. \n" );
        }
        
        return 1; 
}
void reset()
{
        ::reset();
        delete("mark/been_get");
}  
