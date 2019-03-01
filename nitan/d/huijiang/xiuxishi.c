// Room: /d/huijiang/xiuxishi.c
// Last Modified by winder on Sep. 12 2001

inherit RESTROOM_IN;

void create()
{
        set("short", "休息室");
        set("long", @LONG
這是間整潔的廂房，房裡別無他物，只有中間放著一張收拾得舒舒
服服的大床，看著就讓人想睡覺。
LONG );
        set("sleep_room", 1);
        set("no_fight", 1);
        set("no_clean_up", 0);
        set("coor/x", -50070);
        set("coor/y", 9130);
        set("coor/z", 10);
  set("door_name","門");
        set("door_dir","north");
        set("force_name","心硯");
  set("outroom",__DIR__"zoulang2");
        setup();
}