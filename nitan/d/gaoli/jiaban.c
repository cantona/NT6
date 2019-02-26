// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "甲板");
        set("long", @LONG        
這裏是戰船的甲板。有幾名水手不時從你身旁走過，看來都很忙碌。
放眼望去，大海碧波萬傾，一望無際，不禁想駕駛這艘戰船，來闖蕩一番。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north" : __DIR__"shatan2",
                "enter":__DIR__"chuancang",
        ]));
      set("objects",([
          __DIR__"npc/shuishou":1,
          ]));
       setup();
        replace_program(ROOM);
}        
