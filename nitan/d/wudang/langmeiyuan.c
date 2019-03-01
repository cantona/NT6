inherit ROOM;

void create()
{
        set("short", "榔梅園");
        set("long", @LONG
這裡種滿了榔梅樹，花色深淺一如桃花，蒂垂絲作海棠狀。榔和
梅本是山中的兩種樹，相傳有一天玄武帝把梅枝插在榔幹上，久而復
合，成此異種。據說榔梅果核不可帶出武當山，違者必遭不昌。
LONG );
        set("objects", ([
                CLASS_D("wudang") + "/shouyuan": 1,
        ]));
        set("exits", ([
                "northup"  : __DIR__"taiziyan",
                "southup"  : __DIR__"wuyaling",
                "westup"   : __DIR__"nanyanfeng",
        ]));
        set("outdoors", "wudang");
        set("coor/x", -350);
        set("coor/y", -320);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}