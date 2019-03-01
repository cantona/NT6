// Room: /d/qingcheng/xiuxishi.c

inherit RESTROOM_IN;

void create()
{
        set("short", "廂房");
        set("long", @LONG
這是間整潔的廂房，明凈透亮的窗戶用厚厚的窗紗遮了大半，光線
很昏暗。房裡別無他物，只有中間放著一張收拾得舒舒服服的大床，看
著就讓人想睡覺。看來這裡是青城休息的地方。
LONG );
        set("sleep_room", 1);
        set("no_fight", 1);
        set("no_clean_up", 0);
        set("coor/x", -8091);
        set("coor/y", -840);
        set("coor/z", 90);
  set("door_name","大門");
        set("door_dir","east");
        set("force_name","方人智");
  set("outroom",__DIR__"zoulang3");
  setup();
}