// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "草地");
        set("long", @LONG        
這裡是一片青草地。草地柔軟疏鬆，走在上面非常舒服。四周是綠
林環繞，空氣清新，景色秀麗。西邊有一座寺院，看起來規模不是很大。
裡面傳來誦經的聲音。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "southeast" : __DIR__"suishilu2",
                "west":__DIR__"miaodoor",
               ]));
       setup();
        replace_program(ROOM);
}        
