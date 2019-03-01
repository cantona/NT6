// Room: /d/yueyang/feilaizhong.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "飛來鐘");
        set("long", @LONG
原為崇勝寺內古鐘，楊麼起義時以此報警，楊麼高舉“等貴賤，均
貧富”義旗，劫富濟貧，受人民愛戴，便自籌款物鑄成一口大鐘，深夜
偷運上龍山頭，該鐘二毀三造，現四千余斤，遊人到此，總要擊鐘吊古，
告慰忠魂。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("exits", ([
                "northup"   : __DIR__"longsheshan",
                "southdown" : __DIR__"longxianjing",
        ]));
        set("objects", ([
                CLASS_D("gaibang")+"/bangzhong" : 1,
        ]));
        set("coor/x", -1720);
        set("coor/y", 2310);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}