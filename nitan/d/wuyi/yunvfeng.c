// Room: /d/wuyi/yunvfeng.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "玉女峯");
        set("long", @LONG
玉女峯亭亭如少女玉立，突兀挺拔。峯頂花卉參簇，草木蒼翠欲滴，
恰似山花插鬢。巖壁秀潤光滑，宛如玉肌清涼。她俏立溪畔，凜然不可
侵犯，無路攀登。“插花臨水一奇峯，玉骨冰肌處女容”即其寫照。峯
下浴香潭，為玉女沐浴處。峯東圓石如鏡，是為梳粧枱。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "east"      : __DIR__"2qu",
                "southeast" : __DIR__"jingtai",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1380);
        set("coor/y", -5010);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
