// Room: /d/qingcheng/kefang.c

inherit ROOM;

void create()
{
        set("short", "客房");
        set("long", @LONG
這間整潔的廂房是給來青城做客、遊玩的人們準備的房間，明凈透
亮的窗戶用厚厚的窗紗遮了大半。房裡別無他物，只有中間放著一張收
拾得舒舒服服的大床，看著就讓人想睡覺。青城弟子偶爾也來這裡休息。
LONG );
        set("exits", ([
                "north" : __DIR__"zoulang3"
        ]));
        set("sleep_room", 1);
        set("no_fight", 1);
        set("no_clean_up", 0);
        set("coor/x", -8090);
        set("coor/y", -850);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}