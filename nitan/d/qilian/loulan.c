// Room: /d/qilian/loulan.c
// Winder 2000/09/05 

inherit ROOM;

void create()
{
        set("short", "樓蘭廢墟");
        set("long", @LONG
當年樓蘭王傾國力五載，修得這座樓蘭城。後來樓蘭王停止向漢朝
進貢，武帝遣霍去病平之，歷時三載有餘，屠盡樓蘭之民，這裏就成了
一座死城。後過百餘年，樓蘭城就消失了。據傳埋於沙下，不知是否屬
實。
LONG );
        set("outdoors", "qilian");
        set("exits", ([
                "northeast" : __DIR__"jiuquan",
                "west"      : "/d/xingxiu/yueerquan",
        ]));
        set("objects", ([
                "/d/xingxiu/npc/shachong" : 2,
        ]));
        set("coor/x", -20300);
        set("coor/y", 200);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}