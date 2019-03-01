//Cracked by Roath
//Kane
//maco moveed to hangzhou 1999/12/28 

inherit ROOM;

void create()
{
        set("short", "秘室");
        set("long", @LONG
這是酒館碗櫥之後的一座秘室，只有五六尺見方，裡面放了一座
鐵床，一只大鐵箱，但卻絲毫不現得局促，空氣也十分清新，聞不到
一點霉味。
LONG );

        set("no_fight", "1");
        set("resource/water", 1);
        set("exits", ([
                "out" : __DIR__"jiudian",
        ]));

        set("cost", 2);
/*        
        set("item_desc", ([
        "skulls" : "這是一堆共九個人頭骨，分為上中下三層，下層五個，中層三個，上層一個\n",
        ]));
*/

        set("objects", ([
                CLASS_D("taohua") + "/qu" : 1  
        ]));

        setup();
        replace_program(ROOM);
}