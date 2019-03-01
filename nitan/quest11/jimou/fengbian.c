// 風變
#include <mudlib.h>
#include <daemons.h>
#include <ansi.h>

#define WEATHER_CHANNEL "weather"
#define CHANNEL_FORMAT "%%^WEATHER_CHANNEL%%^【%s】%s%%^RESET%%^\n"

void show_wind(string where, int wind);

void main(object ob, string wind)
{
	int i;
	string where;
	object env;
	string *winds = ({"無風", "北風", "東北風", "東風", "東南風", "南風", "西南風", "西風", "西北風",});
	env = environment( ob );
        while( env && !inherits(BASE_ROOM, env) )env = environment( env );
	if( !where = env->get_area() ){
		write("只有在戰場上才能改變風向。\n");
		return;
	};
	if( !wind || !stringp(wind) || member_array(wind, winds) == -1 ){
                write("現在本地區的風向是：" + DAY_D->get_wind_short(AREA_D->get_area(where, "wind")) + "。\n");
		write("無風，北風，東北風，東風，東南風，南風，西南風，西風，或西北風。\n");
                return;
        };
	if( member_array(wind, winds) == AREA_D->get_area(where, "wind") ){
		write("現在的風向就是：" + DAY_D->get_wind_short(AREA_D->get_area(where, "wind")) + "。\n");
		return;
	};

	// In the furture, We have to consider the player's ablility
	// add the exp of this jimou, reduce mp, etc.

	ob->simple_action("$N盤膝而坐，口中念念有詞。\n");
	ob->simple_action("轉眼間，烏雲密布，狂風四起。\n");
	ob->start_busy(10, "你正忙于作法呢。");
	load_object("/daemons/cast_d.c")->reg_player(ob->query_primary_id(), "fengbian");
        ob->award_exp(ob->query_sk_level("sk_zhimou")/2+random(20), "fengbian");
	call_out("show_result", 5+random(5), ob, where, member_array(wind, winds));
}
void show_result(object ob, string where, int wind)
{
	ob->stop_busy();
	if( random(2) == 1 ){
		ob->simple_action("一道閃電從天而降，接著一聲巨響，風向改變了。\n");
		AREA_D->set_area(where, "wind", wind);
		show_wind(where, wind);
	} else {
		ob->simple_action("一道閃電從天而降，正好打在$N身上。\n");
		ob->set_cur_hp(0);
	}
	return;
}
void show_wind(string where, int wind)
{
	string w_info;
	object env, body, *players;
	
	players = users();
	foreach( object user in players ){
		if( !body = user->query_body() )continue;
		if( !env = environment(body) )continue;
		while (env && !inherits(BASE_ROOM, env))env = environment(env);
		if( !(env->get_area()) || env->get_area() != where )continue;
		if( wind ) w_info = "開始吹"+DAY_D->get_wind_short(wind)+"了。";
		else w_info = "風停了。";
		tell(({user}), sprintf(CHANNEL_FORMAT, "天氣", w_info), MSG_INDENT);
	};
	return;
}
