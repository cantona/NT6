inherit ROOM;
void create()
{
        set("short", "山谷口");
        set("long",
"路邊立着一塊石碑，上面寫着兩個古篆字：甘涼。往山谷看去，一條\n"
"彎彎曲曲的小路伸向谷內，一危崖從中斷開。\n"
);
        set("exits", ([
            "out" : "/d/kunlun/shankou",
           "westup": __DIR__"road1",
]));
        set("outdoors","llszhuang");
        setup();
}
