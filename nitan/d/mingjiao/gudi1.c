// Room: /d/mingjiao/gudi1.c

inherit ROOM;

void create()
{
        set("short", "崑崙谷底");
        set("long", @LONG
前面是一堵屏風也似的大山壁。眼前茫茫雲海，更無去路，你竟
是置身在一個三面皆空的極高平台上。那平台倒有十餘丈方圓，可是
半天臨空，上既不得，下又不能，當真是死路一條。這大平台上白皚
皚的都是冰雪，既無樹林，更無野獸。
LONG );
        set("outdoors", "mingjiao");
        setup();
}
void init()
{
        add_action("do_climb","climb");
}
int do_climb()
{
        int n = this_player()->query_skill("dodge",1);
        message_vision("$N深吸了一口氣，慢慢沿着雪壁向上爬。\n", this_player());
        if(n >40)
        {
                message_vision("$N爬了半天，手肘膝蓋都已被堅冰割得鮮血淋漓，終於爬了上來。\n", this_player());
                this_player()->move(__DIR__"gudi2");
        }
        else
        {
                message_vision("$N爬了一會，太累了，不小心滑了下來。唉!沒辦法了，你認命吧。\n", this_player());
                this_player()->receive_damage("qi",15);
                this_player()->receive_wound("qi",10);
        }
        return 1;
}