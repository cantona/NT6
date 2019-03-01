// Last Modified by winder on Jul. 9 2001
// Room: /d/guiyun/shufang.c

inherit ROOM;

void create()
{
        set("short", "書房");
        set("long", @LONG
這裡是莊主平日讀書的地方。進屋門楣上，歪歪斜斜嵌著一個鐵八
卦 (gua)，看起來和房間不太相襯。屋中琳琅滿目，全是詩文典籍；幾
上桌上擺著許多銅器玉器，看來盡是古物。壁上掛著一幅水墨畫(hua)。
房內另有一張竹榻，一位身材高大的中年人正坐在榻上。
LONG );
        set("exits", ([
                "west" : __DIR__"houting",
        ]));
        set("item_desc",([
                "hua" : "
那上面畫的是一個中年書生在月明之夜中庭佇立，手按劍柄，仰天長吁，神情寂寞。
畫的左下角題著一首詞：
“昨夜寒蛩不住鳴。驚回千裡夢，已三更。起來獨自繞階行。人悄悄，簾外月朧明。
  白首為功名。舊山鬆竹老，阻歸程。欲將心事付瑤箏，知音少，弦斷有誰聽？”
下款題著“五湖廢人病中塗鴉”八字。\n"
        ]) );
        set("no_fight", 1);
        set("guacount", 1);

        set("objects", ([
                CLASS_D("taohua")+"/lu" : 1,
                __DIR__"npc/shutong" : 1,
        ]));

        set("coor/x", 250);
        set("coor/y", -830);
        set("coor/z", 0);
        setup();
}
void init()
{
        add_action("do_take","take");
}
int do_take(string arg)
{
        object obn, me = this_player();
        int n;

        n = this_player()->query_skill("dodge",1);
        if( !arg || arg != "gua" )
        {
                write("你要拿什麼呀！\n");
                return 1;
        }
        message_vision("$N在門站定，深呼一口氣，突然躍起。\n", me);
        if(n >= 80 && query("guacount") > 0)
        {
                message_vision("只見$N的身子在空中打了幾個盤旋，身子輕飄飄落回，手中多了一物。\n", me);
                obn = new("/kungfu/class/taohua/obj/bagua");
                obn->move(me);
                addn("guacount",-1);
        }
        else message_vision("$N定睛一看，發現八卦早被人拿走了。\n", me);
        return 1;
}