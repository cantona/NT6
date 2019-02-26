// Room: /d/yanping/yanfumen.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "延福門");
        set("long", @LONG
延福門就是大水門了，門前龍津渡便可放舟直通省城福州。延平府
人煙稠密，廛市繁華，龍蟠虎踞，自古以來為“兵權謀家必爭”。
    駐足城頭延福樓，但見“孤城削壁全臨水，八面無山不到樓。”周
遭山勢壁立，深湍饒郭，易守難攻，其勢佔溪山之雄，當水陸之會，為
入閩之襟喉，省城之屏障，向有“銅延平、鐵邵武”之譽，故關防嚴密
不輕怠。隆武天子以國姓爺食慄此方，賜封延平郡王。
LONG );
        set("exits", ([
                "west"      : __DIR__"road2",
                "north"     : __DIR__"road1",
                "southeast" : __DIR__"longjindu",
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing"    : 2,
        ]));
        set("outdoors", "yanping");
        set("coor/x", 1500);
        set("coor/y", -3000);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}