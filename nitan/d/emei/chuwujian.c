inherit ROOM;

void create()
{
        set("short", "儲物間");
        set("long", @LONG
這裡便是峨嵋華藏庵的儲物間，四周都是架子。一個架上放滿了
各樣兵器，有長劍，拂塵，長鞭等，琳琅滿目。另一個架上放了各種
防具。還有一個架上擺了許多小櫃子，原來是裝滿藥品的藥櫃。一位
師太負責管理這裡的物品，正忙碌著整理防具。後面好象有個小樓梯。
門外就是齋堂了。
LONG );
        set("objects", ([
                CLASS_D("emei") + "/feng" : 1,
                __DIR__"obj/fuchen" : 1,
                __DIR__"obj/zhujian" : 1,
                __DIR__"obj/yaodai" : 1,
        ]));
        set("exits", ([
                "up"    : __DIR__"cangjingge", 
                "north" : __DIR__"hcazhaitang", 
        ]));
        setup();
        replace_program(ROOM);
}