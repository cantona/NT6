// Room: /d/songshan/xiuxishi.c
// Last Modified by winder on Aug. 5 2001

inherit RESTROOM_IN;
void create()
{
        set("short", "休息室");
        set("long", @LONG
這是間整潔的廂房，是嵩山弟子休息起居的地方。因為門窗常年閉
着，房間難免昏暗。房裏靠窗處擺設桌椅，裏邊靠牆放着一張收拾得舒
舒服服的大牀，看着就讓人想睡覺。
LONG );

        set("sleep_room", 1);
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("coor/x", 10);
        set("coor/y", 910);
        set("coor/z", 90);
  set("door_name","門");
        set("door_dir","west");
        set("force_name","湯英鵠");
  set("outroom",__DIR__"eastpath2");
        setup();
}