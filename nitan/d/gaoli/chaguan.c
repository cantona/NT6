// /d/gaoli/chaguan
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "茶館");
        set("long", @LONG
各地的名茶這裏都有的賣。這裏沖茶的水也是從城外專程運來的。
這裏沖茶的壺更是名貴的紫砂壺。這裏沖茶的方法也是最講究的。每壺
茶的第一杯是用來養壺的。所以這裏衝出的茶都有一種純厚的香氣。
LONG
        );
set("exits", ([
               "north":__DIR__"baihu-2", 
        ]));
     set("objects", ([
                "/d/gaoli/npc/chaer" : 1,
               //"/d/gaoli/npc/chake" : 2,
        ]));
     set("resource/water",1);
       setup();
        replace_program(ROOM);
}        
