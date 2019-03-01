// Room: /d/city/beidajie1.c

inherit ROOM;

void create()
{
	set("short", "北大街");
	set("long", @LONG
這是一條寬闊的青石街道，向南北兩頭延伸。北邊是北城門通向城外。南
邊顯得很繁忙。東邊是一家小吃店，店面窄小，恐怕只供應外賣。西邊就是城
隍廟。
LONG
	);
        set("outdoors", "揚州");

	set("exits", ([
		"east" : __DIR__"xiaochidian",
		"south" : __DIR__"beidajie2",
                "west" : __DIR__"chmiao",
		"north" : __DIR__"beimen",
	]));

	set("objects", ([
		CLASS_D("shaolin") + "/xingzhe" : 1
	]));
	set("incity",1);
	setup();
}


 void init()
{
 object me = this_player();
 int t;
 

if(me->query("combat_exp")<100000)
      me->apply_condition("db_exp", 1000);
      
 t = me->query("vip/vip_time") - time();

//if(!me->query("cw_exp"))  me->delete("relife/exp_ext");
if( me->query("rmb_used")>=500  && !me->query("buyvip/start") ) me->set("buyvip/start",1);

if (!me->query("quest/jiuyin1/pass")){
       if( me->query_skill("jiuyin-zhengong")>221) me->set_skill("jiuyin-zhengong",221);
       if( me->query_skill("jiuyin-shenfa")>221) me->set_skill("jiuyin-shenfa",221);
}
if(me->query_skill("taixuan-gong")) {me->delete("taixuan_pass"); 
me->delete_skill("taixuan-gong") ;}




}




