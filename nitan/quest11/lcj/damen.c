// Room: /d/xiangyang/damen.c 大門
// Modify By River 98/10
// Modify By Lklv 2001.9.21
// Modify by tangfeng for 連城訣quest

inherit ROOM;
#include <ansi.h>
#include <wanted.h>

#define QUESTDIR "quest/連城訣/"
#define QUESTDIR1 "quest/連城訣/雪谷激鬥篇/"
#define QUESTDIR2 "quest/連城訣/武館探密篇/"

void create()
{
	set("short", "武館大門");
	set("long", @LONG
這裏是襄陽武館的大門，兩扇黑漆漆的木門向左右敞開着，門口的正上方
高懸着一塊黑底金字的大匾，匾上寫着四個大字：“襄陽武館”。門前的台階
兩旁各立着一個石獅，從大門口向裏面瞧去，武館的院子里人來人往，看起來
好像都很忙碌。大門旁邊站着一個門衞，臉上神情威嚴。
LONG
        );
	set("outdoors","武館");
	set("no_fight", 1);
	set("exits", ([
		"south" : __DIR__"eroad1",
		"enter": "/d/wuguan/menlang",
	]));
	set("objects", ([
                "/d/wuguan/npc/menwei" : 1,
//                "/tmp/ciwei/menwei" : 1,
	]));
	set("incity",1);
	setup();
}

int valid_leave(object me,string dir)
{
	object *obj;
	int x;

	if ( me->query_temp( "wg_help" ) || me->query_temp( "wg_road" ) == 2 )
		return notify_fail("武館門衞説道：" + RANK_D->query_respect(me) +
			"還是再耐心等一會吧，説不定馬上就有人來仗義幫助。\n");
	if ( me->query_temp( "wg_juanzeng" ) )
		me->delete_temp( "wg_juanzeng" );
	if ( me->query_temp( "wg_road" ) == 1 )
		me->delete_temp( "wg_road" );
	if ( dir == "enter" && !wizardp(me)) {
		if ( is_wanted(me) )
			return 0;
		if ( me->query("combat_exp") > 3000 )
		{
			if(!me->query(QUESTDIR1+"over") || me->query(QUESTDIR2+"over"))
				return notify_fail("門衞上前把手一伸：你的武功夠高了，在武館學不到什麼了。\n");
			if(me->query_temp(QUESTDIR2+"start"))
			{
				message_vision(HIY"\n門衞疑惑地看着$N道：$N剛才怎麼進去又出來了？\n", me);
				me->delete_temp("quest/busy");//
				me->delete_temp("quest/連城訣");
				return notify_fail("門衞上前把手一伸：那有這麼好的事情，在武館進進出出。\n");
			}
			obj = users();
			x = sizeof(obj);
			while(x--)
			{
				if ( obj[x]->query_temp(QUESTDIR2+"start") && obj[x]!=me ) 
					return notify_fail("門衞上前把手一伸："+obj[x]->query("name")+RANK_D->query_respect(obj[x]) +"已經去武館探密去了，你再等等！");		  
			}
		}
	}
	if ( dir == "enter" && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"over"))
	{
		message_vision(HIY"\n$N低頭似乎和門衞説了些什麼。門衞啊地一聲叫了出來。\n", me);
		if(me->query(QUESTDIR+"time")&&time()-me->query(QUESTDIR+"time")<86400)
			return notify_fail("門衞上前把手一伸：不管怎樣，今天很忙了，"+RANK_D->query_respect(me) +"先行休息去吧！");		  
		if(me->query(QUESTDIR+"combat_exp")&&me->query("combat_exp")-me->query(QUESTDIR+"combat_exp")<500000)
			return notify_fail("門衞上前把手一伸：以"+RANK_D->query_respect(me) +"目前的經驗就算進去，也做不了什麼，還是抓緊練功吧！");

		message_vision(HIY"門衞啊地一聲跳了起來。\n", me);
		message_vision(HIY"只見門衞往旁邊一閃。$N從門縫裏擠了進去。\n", me);
		me->set(QUESTDIR+"time",time());
		me->set(QUESTDIR+"combat_exp",me->query("combat_exp")); 
		me->set(QUESTDIR2+"start",1);//開始
		me->set_temp(QUESTDIR2+"start",1);
		me->set_temp("quest/busy",1);
	}
	return ::valid_leave(me, dir);
}
