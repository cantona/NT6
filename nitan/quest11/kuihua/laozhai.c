// room: laozhai.c
// modify by Lklv 2001.9.6

#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "向陽老宅");
    set("long", @LONG
這裡是一間破敗的老宅院，平常沒有什麼人會來這裡。地上橫七豎八地堆
著幾件家具。西邊的牆角結著一張蜘蛛網，屋裡到處是塵土，顯然是已經很久
沒有人住了。房間的盡頭有一扇門(men)，但已被坍塌的磚瓦擋住了。
LONG
    );

    	set("exits", ([
        	"west" : __DIR__"xyxiang2",
    	]));

    	set("item_desc", ([
        	"men" : "這扇門已被擋住無法通行，除非你打破(break)它。\n",
    	]) );
	setup();
}

void init()
{
//	object book, me;
//	me = this_player();
	add_action("do_break", "break");
/*
	if ((objectp(book=present("kuihua baodian",me)))) {
		remove_call_out("buqun_rob");
		call_out("buqun_rob", 1, me, book);
	}
*/
}

int do_break(string arg)
{
	int n;
	n = this_player()->query("neili");
	if( !arg || arg!="men" ) {
		write("不要隨隨便便就亂砸別人的東西！\n"); // by pishou
		return 1;
	}
	message_vision("$N走到後門前，拜出騎馬蹲襠式，深吸一口氣，雙掌同時拍出。\n", this_player());

	if (n>=500 && this_player()->query("quest/pixie/pxj_passwd")) {
		message_vision("$N只聽一聲轟響，$N把門震開了！\n", this_player());
		set("exits/south", __DIR__"houyuan");
		this_player()->set("neili",n-500);
		remove_call_out("close");
		call_out("close", 5, this_object());
	}
	else {
		message_vision("$N大吼一聲“開！”，結果什麼也沒發生。看來$N的內力不夠強。\n", this_player());
		this_player()->set("neili",0);
	}
	return 1;
}

void close(object room)
{
	message("vision","門上的磚頭瓦塊稀裡嘩拉坍塌下來，又擋住了後門。\n", room);
	room->delete("exits/south");
}

void buqun_rob(object me, object book)
{
	message_vision(HIY "忽然，一個蒙面人從黑影裡閃了出來，一招「有鳳來儀」，"
        "手中長劍閃爍\n不定，刺向$N的嚥喉！\n" NOR,  me);

	if( !me->query_skill("pixie-jian", 1) ) {
		message_vision("$N一愣之間，已被蒙面人刺中！\n", me);
		book->move(environment(me));
		destruct(book);
		me->unconcious();
	}
	else {
	message_vision("$N身形飄忽，有如鬼魅，轉了幾轉，移步到蒙面人的身後，躲過了"
	"蒙面人這一招。\n", me);
	}
	write("蒙面人雙足點地，越牆而走。\n你感覺蒙面人的身法好像是華山派的。\n");
}
