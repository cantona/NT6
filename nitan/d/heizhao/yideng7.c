//Cracked by Kafei
// yideng quest room 7

inherit ROOM;

void create()
{
        set("short", "缺口");
        set("long", @LONG
山路中間突然中斷，前面的山中間裂開，出現了一個缺口(gap)。
石壁直上直下，下面黑黝黝地深不見低，看來可能是地震造成的。山
路在對面的山上繼續蜿蜒向前。
LONG );
        set("outdoors", "taoyuan");
        set("exits", ([
                "down":__DIR__"yideng5",
        ]));

        set("objects", ([
                CLASS_D("dali") + "/zhuziliu" : 1,
                ]) );

        set("item_desc",([
                "gap" : "這缺口看起來倒是不寬，可以跳過去，但是對面有個書生擋著，如果他在你跳到半空的時候出手攻擊，那你是必死無疑。\n",
                ]));
        
        set("invalid_startroom", 1);
        set("no_clean_up", 0);
        set("coor/x", -38000);
        set("coor/y", -80000);
        set("coor/z", 300);
        setup();
}

void init()
{
        add_action("do_kill", "kill");
        add_action("do_kill", "fight");
        add_action("do_steal", "steal");
        add_action("do_steal", "throw");
}

int do_kill(string arg)
{
        if (arg=="zhu" || arg=="ziliu" || arg=="zhu ziliu") {
                tell_object(this_object(), "隔著這個缺口，你怎麼攻擊他啊？\n");
                return 1;
        }
        return 0;
}

int do_steal(string arg)
{
        tell_object(this_object(), "山頂之上，決無遮掩，你沒有辦法偷襲。\n");
        return 1;
}
