/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : baseball_d.c
 * Author : Clode@RevivalWorld
 * Date   : 2010-08-14
 * Note   : 棒球系統
 * Update :
 *  o 2000-00-00  
 *
 -----------------------------------------
 */

#include <ansi.h>
#include <message.h>
#include <npc.h>
#include <time.h>
#include <skill.h>
#include <baseball.h>
#include <equipment.h>
#include <buff.h>

#define DATA		"/data/daemon/baseball.o"
#define BACKUP_DATA	"/data/daemon/baseball.o.bak"

string *season;
mapping setup;
mapping record;
array games;
private nosave int tick;
private nosave int max_game_times;
int post_season_level;
int post_season_start;
string *post_season_team_8;
string *post_season_team_4;
string *post_season_team_2;
string *post_season_eliminate_teams;
int season_year;

private varargs string *game_finish(int gameindex, string stopid);

private nosave mapping positionname = 
([
	"P" : HIC"投"NOR CYN"手"NOR,
	"C" : HIG"捕"NOR GRN"手"NOR,
	"1B" : HIG"一"NOR GRN"壘手"NOR,
	"2B" : HIG"二"NOR GRN"壘手"NOR,
	"3B" : HIG"三"NOR GRN"壘手"NOR,
	"SS" : HIG"遊"NOR GRN"擊手"NOR,
	"RF" : HIY"右"NOR YEL"外野手"NOR,
	"CF" : HIY"中"NOR YEL"外野手"NOR,
	"LF" : HIY"左"NOR YEL"外野手"NOR,
	"DH" : HIR"指"NOR RED"定打擊"NOR,
]);
private nosave string *pitch_ball_types = ({ "fourseam", "twoseam", "curveball", "slider", "forkball", "sinker" });
private nosave mapping pitch_ball_types_name = 
([
	"fourseam":"四縫線快速球",
	"twoseam":"二縫線快速球",
	"curveball":"曲球",
	"slider":"滑球",
	"forkball":"指叉球",
	"sinker":"伸卡球",
]);

// 調整能力數值，可控制變化率並限制在一定範圍內
int calculate(int value, float decay, int value_max, int to_min, int to_max)
{
	float ratio = (to_max - to_min) / pow(to_float(value_max), decay);
	
	value = to_int( pow(to_float(value), decay) * ratio );
	
	value += to_min;
	
	return value;
}

int calculate_max_game_times(int year)
{
	if( !mapp(record[year]) ) return 0;
		
	max_game_times = 0;
	
	foreach(string team, mapping data in record[year][RECORD_TEAM])
		if( data["win"] + data["lose"] > max_game_times )
			max_game_times = data["win"] + data["lose"];
			
	return max_game_times;
}

int sort_team(string team1, string team2)
{
	int year = season_year;
	int win1, win2, lose1, lose2;
	int limit = (max_game_times-10)/2;
	float winrate1, winrate2;
	
	if( !mapp(record[year]) ) return 0;
		
	if( !mapp(record[year][RECORD_TEAM][team1]) )
		return 1;
		
	if( !mapp(record[year][RECORD_TEAM][team2]) )
		return -1;
		
	win1 = record[year][RECORD_TEAM][team1]["win"];
	win2 = record[year][RECORD_TEAM][team2]["win"];
	lose1 = record[year][RECORD_TEAM][team1]["lose"];
	lose2 = record[year][RECORD_TEAM][team2]["lose"];
	
	if( win1+lose1 == 0 )
		return 1;
	
	if( win2+lose2 == 0 )
		return -1;
		
	winrate1 = to_float(win1)/(win1+lose1);
	winrate2 = to_float(win2)/(win2+lose2);
	
	if( limit < 10 ) limit = 10;
		
	if( win1+lose1 < limit )
	{
		if( win2+lose2 <= limit )
			return winrate1 > winrate2 ? -1 : 1;
				
		return 1;
	}
	
	if( win2+lose2 < limit )
		return -1;

	if( winrate1 == winrate2 )
		return win1 > win2 ? -1 : 1;
	else
		return winrate1 > winrate2 ? -1 : 1;
}

string query_positionname(string code)
{
	return positionname[code];	
}

int save()
{
	save_object(DATA);
}

int backup()
{
	return cp(DATA, BACKUP_DATA);
}

varargs void broadcast(string msg, mapping game)
{
	if( post_season_start && post_season_level > 0 )
	{
		CHANNEL_D->channel_broadcast("sport", msg);
	}
	else
	{
		object user;
		
		foreach(string listener in setup[game[TEAM1]]["listener"] | setup[game[TEAM2]]["listener"] )
			if( objectp(user = find_player(listener)) )
				tell(user, HIG"【棒賽】"NOR+msg+"\n");
	}
}

// 球員或球隊紀錄
mixed add_record(int recordtype, string id, string key, mixed value)
{
	int year = season_year;
	
	if( undefinedp(record[year]) )
	{
		record[year] = allocate_mapping(0);
		record[year][RECORD_TEAM] = allocate_mapping(0);
		record[year][RECORD_PLAYER] = allocate_mapping(0);
		record[year][RECORD_SPECIAL] = allocate_mapping(0);
	}
	
	if( undefinedp(record[year][recordtype][id]) )
		record[year][recordtype][id] = allocate_mapping(0);
		
	if( intp(value) || floatp(value) )
		record[year][recordtype][id][key] += value;
	else
		record[year][recordtype][id][key] = value;
	
	return record[year][recordtype][id][key];
}

varargs mixed get_record(int recordtype, string id, string key, int year)
{
	if( undefinedp(year) )
		year = season_year;
	
	if( undefinedp(record[year]) ||  undefinedp(record[year][recordtype][id]) ) return 0;
		
	return record[year][recordtype][id][key];
}

// 增加球員紀錄
void add_player_record(string id, int number, string key, int value)
{
	string player = setup[id]["roster"][number]["file"];

	add_record(RECORD_PLAYER, player, key, value);
}

// 增加球隊紀錄
void add_team_record(string id, string key, int value)
{
	add_record(RECORD_TEAM, id, key, value);
}

// 確認球隊設定合法
varargs int valid_setup(string id, int all)
{
	object labor;
	object env;
	mapping roster_data;
	object boss = find_player(id);
	int fldaccuracy, fldrange;
	
	if( !mapp(setup[id]) ) return 0;	
	
	if( objectp(boss) )
	{
		setup[id]["username"] = boss->query_idname();
	}
	else if( !stringp(setup[id]["username"]) )
	{
		boss = load_user(id);
			
		setup[id]["username"] = boss->query_idname();	
			
		if( !userp(boss) )
			destruct(boss);	
	}
	
	if( !stringp(setup[id]["name"]) ) return 0;

	if( all )
	{
		setup[id]["outfield"] = 0;
		setup[id]["infield"] = 0;
	}
	
	for(int i=0;i<10;++i)
	{
		roster_data = setup[id]["roster"][i];
		
		if( !mapp(roster_data) )
			return 0;
			
		if( !objectp(labor = roster_data["object"]) )
		{
			if( !file_exists(roster_data["file"]) || !objectp(labor = load_object(roster_data["file"])) )
			{
				setup[id]["roster"][i] = 0;
				return 0;
			}

			roster_data["object"] = labor;
		}

		if( i==0 && labor->query_skill_level("twohands") > 0 )
			return 0;

		env = environment(labor);
		
		if( !objectp(env) || !env->is_module_room() || env->query_building_type() != "baseball" || query("owner", env) != query("boss", labor) || query("job/type", labor) != SPORTER )
		{
			setup[id]["roster"][i] = 0;
			return 0;
		}
		
		if( all )
		{
			roster_data[BUFF_BATTER_POWER] = labor->query_equipment_buff(BUFF_BATTER_POWER);
			roster_data[BUFF_PITCHER_POWER] = labor->query_equipment_buff(BUFF_PITCHER_POWER);
			roster_data[BUFF_FIELDER_POWER] = labor->query_equipment_buff(BUFF_FIELDER_POWER);

			fldaccuracy = labor->query_skill_level("fldaccuracy") + roster_data[BUFF_FIELDER_POWER];
			fldrange = labor->query_skill_level("fldrange") + roster_data[BUFF_FIELDER_POWER];
				
			switch(roster_data["position"])
			{
				case "P": setup[id]["infield"] += fldaccuracy * 4 / 5 + fldrange * 1 / 5 + labor->query_agi()/2; break;
				case "C": setup[id]["infield"] += fldaccuracy * 4 / 5 + fldrange * 1 / 5 + labor->query_agi()/2; break;
				case "1B": setup[id]["infield"] += fldaccuracy * 2 / 3 + fldrange * 1 / 3 + labor->query_agi()/2; break;
				case "2B": setup[id]["infield"] += fldaccuracy * 2 / 3 + fldrange * 1 / 3 + labor->query_agi()/2; break;
				case "3B": setup[id]["infield"] += fldaccuracy * 2 / 3 + fldrange * 1 / 3 + labor->query_agi()/2; break;
				case "SS": setup[id]["infield"] += fldaccuracy * 2 / 3 + fldrange * 1 / 3 + labor->query_agi()/2; break;
				case "RF": setup[id]["outfield"] += fldaccuracy * 1 / 4 + fldrange * 3 / 4 + labor->query_agi()/2; break;
				case "CF": setup[id]["outfield"] += fldaccuracy * 1 / 4 + fldrange * 3 / 4 + labor->query_agi()/2; break;
				case "LF": setup[id]["outfield"] += fldaccuracy * 1 / 4 + fldrange * 3 / 4 + labor->query_agi()/2; break;
				case "DH": break;
			}
			
			if( i == 9 )
			{
				setup[id]["outfield"] = calculate(setup[id]["outfield"], 0.8, 999*3, 500, 1000);
				setup[id]["infield"] = calculate(setup[id]["infield"], 0.8, 999*6, 500, 1000);
			}	
		}
	}
	
	return 1;
}

// 計算球隊每場比賽應有收入
int query_income(string id)
{
	int year = season_year;
	int win, lose;
	
	if( !valid_setup(id) || !mapp(record[year]) || !mapp(record[year][RECORD_TEAM][id]) ) 
		return 0;	
	
	win = record[year][RECORD_TEAM][id]["win"];
	lose = record[year][RECORD_TEAM][id]["lose"];

	if( win + lose <= 0 ) return 0;

	return BASEINCOME * win / (win + lose);
}

string query_player_status(object player)
{
	string id = query("boss", player);
	mapping data;
	
	if( !undefinedp(setup[id]) && arrayp(setup[id]["roster"]) )
	{
		for(int i=0;i<10;++i)
		{
			data = setup[id]["roster"][i];
			
			if( !mapp(data) ) continue;

			if( data["file"] == base_name(player) )
				return positionname[data["position"]]+" "+(i > 0 ? GRN"第 "HIG+i+NOR GRN" 棒 "NOR:"");
		}	
	}
	
	return "";
}

// 球隊設定
void set_setup(string id, mapping newsetup)
{
	setup[id] += newsetup;
	
	save();
}

// 刪除球隊設定
void delete_setup(string id)
{
	map_delete(setup, id);
	
	save();
}

// 加入季賽
void join_season(string id)
{
	int index;
	
	// 已經加入季賽
	if( member_array(id, season) != -1 ) return;
		
	season = sort_array(season, (: random(2) ? 1 : -1 :));

	foreach(string oldid in season)
	{
		index = random(sizeof(setup[oldid]["opponents"]));
	
		if( member_array(id, setup[oldid]["opponents"]) == -1 )
			setup[oldid]["opponents"] = setup[oldid]["opponents"][0..index] + ({ id }) + setup[oldid]["opponents"][index+1..];
	}
	
	if( !sizeof(setup[id]["opponents"]) )
		setup[id]["opponents"] = copy(sort_array(season, (: random(2) ? 1 : -1 :)));

	setup[id]["listener"] |= ({ id });

	season |= ({ id });		
}

// 取消比賽
varargs void cancel_game(string id, int force)
{
	int gamessize = sizeof(games);
	
	for(int i=0;i<gamessize;++i)
	{
		if( !mapp(games[i]) ) continue;
		
		if( games[i][TEAM1] == id || games[i][TEAM2] == id )
		{
			if( force )
			{
				if( games[i][TEAM1] == id )
					game_finish(i, id);
				else if( games[i][TEAM2] == id )
					game_finish(i, id);
			}
			else
			{
				setup[games[i][TEAM1]]["status"] = STATUS_IDLE;
				setup[games[i][TEAM2]]["status"] = STATUS_IDLE;
				
				games[i] = 0;
			}
		}
	}
	
	games -= ({ 0 });
}

// 退出季賽
void leave_season(string id)
{
	if( member_array(id, season) == -1 ) return;

	foreach(string oldid in season)
		setup[oldid]["opponents"] -= ({ id });

	cancel_game(id);

	season -= ({ id });
}

// 是否加入季賽
int in_season(string id)
{
	return member_array(id, season) != -1;
}

// 是否正在比賽中
int query_status(string id)
{
	if( !in_season(id) ) return 0;
		
	return setup[id]["status"];
}

// 比賽結束
private varargs string *game_finish(int gameindex, string stopid)
{
	int year = season_year;
	string *msg = allocate(0);
	mapping game = games[gameindex];
	string team1name = setup[game[TEAM1]]["name"];
	string team2name = setup[game[TEAM2]]["name"];
	string income_msg = HIG"收入"NOR GRN"分配"NOR;
	string finalscore;
	string winteam, loseteam;
	
	if( !undefinedp(stopid) && stringp(stopid) )
	{
		if( game[TEAM1] == stopid )
			game[TEAM1SCORE] = -1;
		else if( game[TEAM2] == stopid )
			game[TEAM2SCORE] = -1;	
	}

	if( game[TEAM1SCORE] > game[TEAM2SCORE] )
	{
		winteam = game[TEAM1];
		loseteam = game[TEAM2];
	}
	else
	{
		winteam = game[TEAM2];
		loseteam = game[TEAM1];
	}
	finalscore = HIG"比賽"NOR GRN"結果"NOR" 雙方"+(game[INNING]>18?"一共纏鬥了 "+(game[INNING]/2+game[INNING]%2)+" 局，":"")+"比分為"+setup[game[TEAM2]]["username"]+"“"+team2name+" "+game[TEAM2SCORE]+" : "+game[TEAM1SCORE]+" "+team1name+"”"+setup[game[TEAM1]]["username"];
	
	switch(game[TEAM1SCORE] - game[TEAM2SCORE])
	{
		case -999..-16:		msg += ({ finalscore+"，可憐的“"+team1name+"”遭到了恐怖的血腥屠殺" });	break;
		case -15..-11:		msg += ({ finalscore+"，“"+team2name+"”徹底的羞辱了對手" });			break;
		case -10..-6:		msg += ({ finalscore+"，“"+team2name+"”不留顏面地痛宰了對手" });		break;
		case -5..-3:		msg += ({ finalscore+"，“"+team2name+"”在這場比賽中輕鬆獲勝" });		break;
		case -2..-1:		msg += ({ finalscore+"，“"+team2name+"”在驚險中獲勝" });			break;
		case 1..2:		msg += ({ finalscore+"，“"+team1name+"”在驚險中獲勝" });			break;
		case 3..5:		msg += ({ finalscore+"，“"+team1name+"”在這場比賽中輕鬆獲勝" });		break;
		case 6..10:		msg += ({ finalscore+"，“"+team1name+"”不留顏面地痛宰了對手" });		break;
		case 11..15:		msg += ({ finalscore+"，“"+team1name+"”徹底的羞辱了對手" });			break;
		case 16..999:		msg += ({ finalscore+"，可憐的“"+team2name+"”遭到了恐怖的血腥屠殺" });	break;
		//default: error("error score");
	}
	
	if( !post_season_level )
	{	
		add_team_record(winteam, "win", 1);
		add_team_record(loseteam, "lose", 1);

		if( setup[winteam]["keeploses"] >= 5 )
		{
			msg += ({ "“"+setup[winteam]["name"]+"”中止了最近的 "HIG+setup[winteam]["keeploses"]+NOR" 連敗。" });
		}
		if( setup[loseteam]["keepwins"] >= 5 )
		{
			msg += ({ "“"+setup[loseteam]["name"]+"”中止了最近的 "HIR+setup[loseteam]["keepwins"]+NOR" 連勝。" });
		}
			
		setup[winteam]["keepwins"]++;
		setup[winteam]["keeploses"] = 0;
		
		setup[loseteam]["keepwins"] = 0;
		setup[loseteam]["keeploses"]++;
		
		if( setup[winteam]["keepwins"] > record[year][RECORD_SPECIAL]["keepwins"] )
		{
			record[year][RECORD_SPECIAL]["keepwins"] = setup[winteam]["keepwins"];
			record[year][RECORD_SPECIAL]["keepwinsteam"] = winteam;
			
			msg += ({ HIY"紀錄"NOR YEL"更新 "NOR"士氣高昂的“"+setup[winteam]["name"]+"”突破本季最長連勝紀錄，"HIR"連勝"NOR RED"紀錄"NOR"來到第 "HIR+setup[winteam]["keepwins"]+NOR" 場" });
		}
		else if( setup[winteam]["keepwins"] >= 5 )
		{
			msg += ({ "“"+setup[winteam]["name"]+"”打出一波 "HIR+setup[winteam]["keepwins"]+NOR" 連勝，戰績大幅躍進" });
		}
		
		if( setup[loseteam]["keeploses"] > record[year][RECORD_SPECIAL]["keeploses"] )
		{
			record[year][RECORD_SPECIAL]["keeploses"] = setup[loseteam]["keeploses"];
			record[year][RECORD_SPECIAL]["keeplosesteam"] = loseteam;
			
			msg += ({ HIY"紀錄"NOR YEL"更新 "NOR"士氣低落的“"+setup[loseteam]["name"]+"”苦吞本季最長連敗紀錄，"HIG"連敗"NOR GRN"紀錄"NOR"來到第 "HIG+setup[loseteam]["keeploses"]+NOR" 場" });
		}
		else if( setup[loseteam]["keeploses"] >= 5 )
		{
			msg += ({ "“"+setup[loseteam]["name"]+"”連續吞下 "HIG+setup[loseteam]["keeploses"]+NOR" 連敗，戰績大幅退後" });
		}
	}
	
	// 單場最多三振紀錄
	if( game[TEAM1K] > game[TEAM2K] && game[TEAM1K] > record[year][RECORD_SPECIAL]["maxstrikeouts"] )
	{
		record[year][RECORD_SPECIAL]["maxstrikeouts"] = game[TEAM1K];
		record[year][RECORD_SPECIAL]["maxstrikeoutsplayer"] = setup[game[TEAM1]]["roster"][0]["file"];
		
		msg += ({ HIY"紀錄"NOR YEL"更新 "NOR"“"+team1name+"”的"+setup[game[TEAM1]]["roster"][0]["object"]->query_idname()+"突破本季投手單場最多三振紀錄，紀錄來到 "HIY+game[TEAM1K]+NOR YEL"K"NOR" ！！" });
	}
	else if( game[TEAM2K] > game[TEAM1K] && game[TEAM2K] > record[year][RECORD_SPECIAL]["maxstrikeouts"] )
	{
		record[year][RECORD_SPECIAL]["maxstrikeouts"] = game[TEAM2K];
		record[year][RECORD_SPECIAL]["maxstrikeoutsplayer"] = setup[game[TEAM2]]["roster"][0]["file"];
		
		msg += ({ HIY"紀錄"NOR YEL"更新 "NOR"“"+team2name+"”的"+setup[game[TEAM2]]["roster"][0]["object"]->query_idname()+"突破本季投手單場最多三振紀錄，紀錄來到 "HIY+game[TEAM2K]+NOR YEL"K"NOR" ！！" });
	}
	
	// 單場最多安打紀錄
	if( game[TEAM1HIT] > game[TEAM2HIT] && game[TEAM1HIT] > record[year][RECORD_SPECIAL]["maxhits"] )
	{
		record[year][RECORD_SPECIAL]["maxhits"] = game[TEAM1HIT];
		record[year][RECORD_SPECIAL]["maxhitsteam"] = game[TEAM1];
		
		msg += ({ HIY"紀錄"NOR YEL"更新 "NOR"“"+team1name+"”突破本季單場最多安打紀錄，紀錄來到 "HIY+game[TEAM1HIT]+NOR YEL" 只安打"NOR" ！！" });
	}
	else if( game[TEAM2HIT] > game[TEAM1HIT] && game[TEAM2HIT] > record[year][RECORD_SPECIAL]["maxhits"] )
	{
		record[year][RECORD_SPECIAL]["maxhits"] = game[TEAM2HIT];
		record[year][RECORD_SPECIAL]["maxhitsteam"] = game[TEAM2];
		
		msg += ({ HIY"紀錄"NOR YEL"更新 "NOR"“"+team2name+"”突破本季單場最多安打紀錄，紀錄來到 "HIY+game[TEAM2HIT]+NOR YEL" 只安打"NOR" ！！" });
	}
		
	// 單場最多得分紀錄
	if( game[TEAM1SCORE] > game[TEAM2SCORE] && game[TEAM1SCORE] > record[year][RECORD_SPECIAL]["maxscores"] )
	{
		record[year][RECORD_SPECIAL]["maxscores"] = game[TEAM1SCORE];
		record[year][RECORD_SPECIAL]["maxscoresteam"] = game[TEAM1];
		
		msg += ({ HIY"紀錄"NOR YEL"更新 "NOR"“"+team1name+"”突破本季單場最多得分紀錄，紀錄來到 "HIY+game[TEAM1SCORE]+NOR YEL" 分"NOR" ！！" });
	}
	else if( game[TEAM2SCORE] > game[TEAM1SCORE] && game[TEAM2SCORE] > record[year][RECORD_SPECIAL]["maxscores"] )
	{
		record[year][RECORD_SPECIAL]["maxscores"] = game[TEAM2SCORE];
		record[year][RECORD_SPECIAL]["maxscoresteam"] = game[TEAM2];
		
		msg += ({ HIY"紀錄"NOR YEL"更新 "NOR"“"+team2name+"”突破本季單場最多得分紀錄，紀錄來到 "HIY+game[TEAM2SCORE]+NOR YEL" 分"NOR" ！！" });
	}
	
	// 單場最多局數紀錄
	if( game[INNING] > record[year][RECORD_SPECIAL]["maxinnings"] )
	{
		record[year][RECORD_SPECIAL]["maxinnings"] = game[INNING];
		record[year][RECORD_SPECIAL]["maxinningsteam1"] = game[TEAM1];
		record[year][RECORD_SPECIAL]["maxinningsteam2"] = game[TEAM2];
		
		msg += ({ HIY"紀錄"NOR YEL"更新 "NOR"“"+team1name+"”與“"+team2name+"”共同創造本季單場延長賽最多局數紀錄，紀錄來到 "HIY+(game[INNING]/2 + game[INNING]%2)+NOR YEL" 局"NOR" ！！" });
	}
	
	// 單場分數差最多紀錄
	if( abs(game[TEAM1SCORE] - game[TEAM2SCORE]) > record[year][RECORD_SPECIAL]["maxscorediff"] )
	{
		record[year][RECORD_SPECIAL]["maxscorediff"] = abs(game[TEAM1SCORE] - game[TEAM2SCORE]);
		record[year][RECORD_SPECIAL]["maxscorediffwin"] = game[TEAM1SCORE] > game[TEAM2SCORE] ? game[TEAM1] : game[TEAM2];
		record[year][RECORD_SPECIAL]["maxscoredifflose"] = game[TEAM1SCORE] < game[TEAM2SCORE] ? game[TEAM1] : game[TEAM2];
		
		msg += ({ HIY"紀錄"NOR YEL"更新 "NOR"“"+team1name+"”與“"+team2name+"”共同創造本季單場分數差距最大紀錄，紀錄來到 "HIY+abs(game[TEAM1SCORE] - game[TEAM2SCORE])+NOR YEL" 分"NOR" ！！" });
	}
	
	setup[game[TEAM1]]["status"] = STATUS_IDLE;
	setup[game[TEAM2]]["status"] = STATUS_IDLE;

	if( !post_season_level )
		for(int i=0;i<sizeof(msg);++i)
			call_out((: CHANNEL_D->channel_broadcast("sport", $(msg)[$(i)]) :), 0);
			
	if( undefinedp(stopid) )
	{
		int income;
		int total_income = query_income(game[TEAM1]) + query_income(game[TEAM2]);
		
		if( file_exists(setup[game[TEAM2]]["master"]) )
		{
			object master = load_object(setup[game[TEAM2]]["master"]);
			
			income = total_income * 10 / 100;
			income += total_income * 80 / 100 * game[TEAM2SCORE] / (game[TEAM1SCORE]+game[TEAM2SCORE]);
			
			if( post_season_level && post_season_start )
				income *= 20;
				
			if( query("owner", master) == game[TEAM2] && objectp(find_player(game[TEAM2])) )
			{
				addn("money", income, master);
				income_msg += "“"+setup[game[TEAM2]]["name"]+"”獲得票房收入 "HIY+money(MONEY_D->query_default_money_unit(), income)+NOR;
							
				master->save();
			}
		}
		
		if( file_exists(setup[game[TEAM1]]["master"]) )
		{
			object master = load_object(setup[game[TEAM1]]["master"]);
			
			income = total_income * 10/ 100;
			income += total_income * 80 / 100 * game[TEAM1SCORE] / (game[TEAM1SCORE]+game[TEAM2SCORE]);
			
			if( post_season_level && post_season_start )
				income *= 20;
	
			if( query("owner", master) == game[TEAM1] && objectp(find_player(game[TEAM1])) )
			{
				addn("money", income, master);
				income_msg += "“"+setup[game[TEAM1]]["name"]+"”獲得票房收入 "HIY+money(MONEY_D->query_default_money_unit(), income)+" "NOR;
				
				master->save();
			}
		}
		
		if( income_msg != HIG"收入"NOR GRN"分配"NOR )
			msg += ({ income_msg });
	}

	if( post_season_start )
	{		
		switch(post_season_level)
		{
			case 1..4: 
			{
				if( game[TEAM1SCORE] > game[TEAM2SCORE] )
				{
					post_season_team_4 |= ({ game[TEAM1] });
					msg += ({ HIR"季後"NOR RED"賽"NOR" "+setup[game[TEAM1]]["username"]+"領軍的“"+setup[game[TEAM1]]["name"]+"”獲得四強晉級！！" });
					post_season_eliminate_teams |= ({ game[TEAM2] });
				}
				else
				{
					post_season_team_4 |= ({ game[TEAM2] });
					msg += ({ HIR"季後"NOR RED"賽"NOR" "+setup[game[TEAM2]]["username"]+"領軍的“"+setup[game[TEAM2]]["name"]+"”獲得四強晉級！！" });
					post_season_eliminate_teams |= ({ game[TEAM1] });
				}
				save();
				break;
			}
			case 5..6:
			{
				if( game[TEAM1SCORE] > game[TEAM2SCORE] )
				{
					post_season_team_2 |= ({ game[TEAM1] });
					msg += ({ HIR"季後"NOR RED"賽"NOR" "+setup[game[TEAM1]]["username"]+"領軍的“"+setup[game[TEAM1]]["name"]+"”獲得晉級總冠軍賽！！" });
					post_season_eliminate_teams |= ({ game[TEAM2] });
				}
				else
				{
					post_season_team_2 |= ({ game[TEAM2] });
					msg += ({ HIR"季後"NOR RED"賽"NOR" "+setup[game[TEAM2]]["username"]+"領軍的“"+setup[game[TEAM2]]["name"]+"”獲得晉級總冠軍賽！！" });
					post_season_eliminate_teams |= ({ game[TEAM1] });
				}
				save();
				break;
			}
			case 7:
			{
				object user;
				
				if( game[TEAM1SCORE] > game[TEAM2SCORE] )
				{
					msg += ({ HIR"季後"NOR RED"賽"NOR" 恭喜"+setup[game[TEAM1]]["username"]+"領軍的“"+setup[game[TEAM1]]["name"]+"”獲得"NOR CYN"第 "HIC+year+NOR CYN" 球季"HIY"棒球"NOR YEL"世界冠軍"NOR"！！" });
					record[year][RECORD_SPECIAL]["champion"] = game[TEAM1];
					record[year][RECORD_SPECIAL]["2rd"] = game[TEAM2];
					post_season_eliminate_teams |= ({ game[TEAM2] });
					user = load_user(game[TEAM1]);
				}
				else
				{
					msg += ({ HIR"季後"NOR RED"賽"NOR" 恭喜"+setup[game[TEAM2]]["username"]+"領軍的“"+setup[game[TEAM2]]["name"]+"”獲得"NOR CYN"第 "HIC+year+NOR CYN" 球季"HIY"棒球"NOR YEL"世界冠軍"NOR"！！" });
					record[year][RECORD_SPECIAL]["champion"] = game[TEAM2];
					record[year][RECORD_SPECIAL]["2rd"] = game[TEAM1];
					post_season_eliminate_teams |= ({ game[TEAM1] });
					
					user = load_user(game[TEAM2]);
				}
				
				if( objectp(user) )
				{
					object ring = new("/obj/baseball/champion_ring_"+year);
					
					user->add_title(sprintf(HIC+"%-4d"+HIY"總"NOR YEL"冠"NOR YEL"軍"NOR, year));
					user->save();				
					
					tell(user, pnoun(2, user)+"獲得一隻“"+ring->query_idname()+"”。\n");
					CHANNEL_D->channel_broadcast("sport", user->query_idname()+"獲得一隻“"+ring->query_idname()+"”。");
					
					ring->set_keep();
					ring->move(user);
					
					if( !userp(user) )
						destruct(user);
				}
					
				save();
					
				break;
			}
		}
	}
	
	if( !random(10) )
	{
		int status;
		object *equipments;
		
		foreach(mapping roster_data in setup[game[TEAM1]]["roster"] + setup[game[TEAM2]]["roster"])
		{
			if( !objectp(roster_data["object"]) ) continue;
				
			equipments = roster_data["object"]->query_equipping_object(EQ_MITT[PART_ID]) || allocate(0);
			equipments |= roster_data["object"]->query_equipping_object(EQ_BAT[PART_ID]) || allocate(0);
			
			if( !sizeof(equipments) ) continue;
				
			equipments = sort_array(equipments, (: random(2) ? 1 : -1 :));
				
			if( !random(25) )
			{
				msg += ({ roster_data["object"]->query_idname()+"所使用的"+equipments[0]->query_idname()+"在這場比賽中壞掉了！！\n" });
				
				roster_data["object"]->unequip(equipments[0], ref status);
				
				destruct(equipments[0], 1);
			}
		}
	}
			
	games[gameindex] = 0;
	//games -= ({ 0 });

	return msg;
}

// 計算分數
private string *new_score(int gameindex, string attacker, string defender, int score, int scoretype)
{
	string *msg = allocate(0);
	mapping game = games[gameindex];
	int attacknumber;
	
	// 計算得分
	if( attacker == game[TEAM1] )
	{
		game[TEAM1SCORE] += score;
		attacknumber = game[TEAM1NUMBER];
	}
	else
	{
		game[TEAM2SCORE] += score;
		attacknumber = game[TEAM2NUMBER];
	}
		
	add_player_record(defender, 0, "run", score);
	add_player_record(attacker, attacknumber, "rbi", score);
	
	msg += ({ "“"+setup[game[TEAM2]]["name"]+" "+game[TEAM2SCORE]+" : "+game[TEAM1SCORE]+" "+setup[game[TEAM1]]["name"] +"”" });
	
	// 下半局，再見得分
	if( game[INNING] >= 18 && (game[INNING] % 2) == 0 && game[TEAM1SCORE] > game[TEAM2SCORE] )
	{
		switch(scoretype)
		{
			case SCORETYPE_HOMERUN:		msg += ({ "這是一隻再見全壘打！！" }); 	break;
			case SCORETYPE_FOURBALL:	msg += ({ "這是一個再見四壞！！" }); 	break;
			case SCORETYPE_SACRIFICE:	msg += ({ "這是一隻再見犧牲打！！" });	break;
			case SCORETYPE_HIT:		msg += ({ "這是一隻再見安打！！" }); 	break;
			default: error("error scoretype");
		}

		msg += game_finish(gameindex);
	}
	
	return msg;
}

// 計算新的出局數
private string *new_out(int gameindex, string attacker, string defender, int outcount, int outtype)
{
	string *msg = allocate(0);
	mapping game = games[gameindex];
	int attackernumber = attacker == game[TEAM1] ? game[TEAM1NUMBER] : game[TEAM2NUMBER];
		
	game[STRIKE] = 0;
	game[BALL] = 0;

	// 打席次數紀錄
	add_player_record(attacker, attackernumber, "ab", 1);
	
	// 投手對決人次紀錄
	add_player_record(defender, 0, "bf", 1);
	
	// 投手對決出局數
	add_player_record(defender, 0, "out", outcount);
	
	if( outtype == BASETYPE_STRIKEOUT )
		add_player_record(defender, 0, "strikeout", 1);	
			
	if( (game[OUT]+=outcount) >= 3 )
	{			
		game[OUT] = 0;

		if( game[INNING] >= 17 && (((game[INNING] % 2) && game[TEAM1SCORE] > game[TEAM2SCORE]) || (!(game[INNING] % 2) && game[TEAM1SCORE] != game[TEAM2SCORE])))
			return game_finish(gameindex);
		
		game[INNING]++;
		
		msg += ({ "“"+setup[game[TEAM2]]["name"]+" "+game[TEAM2SCORE]+" : "+game[TEAM1SCORE]+" "+setup[game[TEAM1]]["name"] +"”攻守交替，比賽進入到"+(game[INNING]>=19?"延長賽":"")+"第 "+( game[INNING]%2 ? ((game[INNING]+1)/2)+" 局上半" : ((game[INNING]+1)/2)+" 局下半" ) });
			
		game[RUNNER1ST] = 0;
		game[RUNNER2ND] = 0;
		game[RUNNER3RD] = 0;
	}
	else
	{	
		// 刺殺, 有機會進壘
		if( outtype == BASETYPE_BUNT || outtype == BASETYPE_TOUCHKILL )
		{
			// 滿壘則封殺三壘跑者
			if( game[RUNNER3RD] > 0 && game[RUNNER2ND] > 0 && game[RUNNER1ST] > 0 )
			{
				game[RUNNER3RD] = game[RUNNER2ND];
				game[RUNNER2ND] = game[RUNNER1ST];
				game[RUNNER1ST] = attackernumber;
			}
			else
			{
				// 三壘無人 二壘有人, 進壘
				if( game[RUNNER3RD] == 0 && game[RUNNER2ND] > 0 )
				{
					game[RUNNER3RD] = game[RUNNER2ND];
					game[RUNNER2ND] = 0;
				}
				
				// 二壘無人 一壘有人, 進壘
				if( game[RUNNER2ND] == 0 && game[RUNNER1ST] > 0 )
				{
					game[RUNNER2ND] = game[RUNNER1ST];
					game[RUNNER1ST] = 0;
				}
			}	
		}
		// 接殺, 有機會進壘
		else if( outtype == BASETYPE_CATCHKILL )
		{
			if( game[RUNNER3RD] > 0 )
			{
				msg += ({ "“"+setup[attacker]["name"]+"”三壘跑者衝回本壘得分！" });
				msg += new_score(gameindex, attacker, defender, 1, SCORETYPE_SACRIFICE);
				
				if( !games[gameindex] )
					return msg;

				game[RUNNER3RD] = 0;
			}
		}
		// 雙殺, 有機會進壘
		else if( outtype == BASETYPE_DOUBLEPLAY )
		{
			// 三壘無人 二壘有人, 進壘
			if( game[RUNNER2ND] > 0 )
			{
				game[RUNNER3RD] = game[RUNNER2ND];
				game[RUNNER2ND] = 0;
			}
			
			game[RUNNER1ST] = 0;
		}
		// 三殺 , 理論上不會執行到此(直接換局)
		//else if( outtype == BASETYPE_TRIPLEPLAY ) { }
		
		if( game[RUNNER3RD] > 0 || game[RUNNER2ND] > 0 || game[RUNNER1ST] > 0 )
			msg += ({ "“"+setup[attacker]["name"]+"”目前壘上的跑者情形為 [ "+(game[RUNNER3RD] > 0?HIW"○"NOR:WHT"╳"NOR)+" "+(game[RUNNER2ND] > 0?HIW"○"NOR:WHT"╳"NOR)+" "+(game[RUNNER1ST] > 0?HIW"○"NOR:WHT"╳"NOR)+" ] "HIW+game[OUT]+NOR WHT"out"NOR });
	}

	// 輪下一棒
	if( attacker == game[TEAM1] )
		game[TEAM1NUMBER] = 1 + (game[TEAM1NUMBER] % 9);
	else
		game[TEAM2NUMBER] = 1 + (game[TEAM2NUMBER] % 9);
		
	setup[attacker]["hint"] = 0;
	setup[defender]["hint"] = 0;
	
	games[gameindex] = game;
	
	return msg;
}

// 計算新的進壘
private string *new_base(int gameindex, string attacker, string defender, int basecount, int basetype)
{
	string *msg = allocate(0);
	mapping game = games[gameindex];

	int score = 0;
	int attacknumber = attacker == game[TEAM1] ? game[TEAM1NUMBER] : game[TEAM2NUMBER];
	
	if( basecount <= 0 ) error("basecount_error");

	game[STRIKE] = 0;
	game[BALL] = 0;

	// 投手對決人次
	add_player_record(defender, 0, "bf", 1);

	if( basetype == BASETYPE_HIT ) // 安打進壘
	{
		int scoretype;
		
		// 打者打擊次數紀錄
		add_player_record(attacker, attacknumber, "ab", 1);

		if( attacker == game[TEAM1] )
			game[TEAM1HIT]++;
		else
			game[TEAM2HIT]++;
			
		switch(basecount)
		{
			case 1:
			{
				add_player_record(attacker, attacknumber, "hit1", 1);
				add_player_record(attacker, attacknumber, "hit", 1);
				
				if( game[RUNNER3RD] > 0 ) {	score++; msg += ({ "“"+setup[attacker]["name"]+"”三壘跑者奔回本壘得分！" }); game[RUNNER3RD] = 0; }	
				if( game[RUNNER2ND] > 0 )
				{
					if( random(setup[attacker]["roster"][game[RUNNER2ND]]["object"]->query_int()) > random(400) )
					{
						score++; 
						msg += ({ "“"+setup[attacker]["name"]+"”二壘跑者奔回本壘得分！" });	
					
						game[RUNNER2ND] = 0; 
					}
					else
					{
						game[RUNNER3RD] = game[RUNNER2ND];
						game[RUNNER2ND] = 0; 
					}
				}
						
				// 一壘有人，進壘
				if( game[RUNNER1ST] > 0 )
				{
					if( game[RUNNER3RD] > 0 )
						game[RUNNER2ND] = game[RUNNER1ST];
					else
						game[RUNNER3RD] = game[RUNNER1ST];
						
					game[RUNNER1ST] = 0;
				}
				
				// 打者上到一壘
				game[RUNNER1ST] = (attacker == game[TEAM1] ? game[TEAM1NUMBER] : game[TEAM2NUMBER]);
				
				scoretype = SCORETYPE_HIT;
				
				break;
			}
			case 2:
			{
				add_player_record(attacker, attacknumber, "hit2", 1);
				add_player_record(attacker, attacknumber, "hit", 1);
				
				if( game[RUNNER3RD] > 0 ) {	score++; msg += ({ "“"+setup[attacker]["name"]+"”三壘跑者奔回本壘得分！" }); game[RUNNER3RD] = 0; }	
				if( game[RUNNER2ND] > 0 ) {	score++; msg += ({ "“"+setup[attacker]["name"]+"”二壘跑者奔回本壘得分！" }); game[RUNNER2ND] = 0; }
				if( game[RUNNER1ST] > 0 ) {	score++; msg += ({ "“"+setup[attacker]["name"]+"”一壘跑者奔回本壘得分！" }); game[RUNNER1ST] = 0; }
				
				// 打者上到二壘
				game[RUNNER2ND] = (attacker == game[TEAM1] ? game[TEAM1NUMBER] : game[TEAM2NUMBER]);
	
				scoretype = SCORETYPE_HIT;
				
				break;	
			}
			case 3:
			{
				add_player_record(attacker, attacknumber, "hit3", 1);
				add_player_record(attacker, attacknumber, "hit", 1);
				
				if( game[RUNNER3RD] > 0 ) {	score++; msg += ({ "“"+setup[attacker]["name"]+"”三壘跑者奔回本壘得分！" }); game[RUNNER3RD] = 0; }	
				if( game[RUNNER2ND] > 0 ) {	score++; msg += ({ "“"+setup[attacker]["name"]+"”二壘跑者奔回本壘得分！" }); game[RUNNER2ND] = 0; }
				if( game[RUNNER1ST] > 0 ) {	score++; msg += ({ "“"+setup[attacker]["name"]+"”一壘跑者奔回本壘得分！" }); game[RUNNER1ST] = 0; }
							
				// 打者上到三壘
				game[RUNNER3RD] = (attacker == game[TEAM1] ? game[TEAM1NUMBER] : game[TEAM2NUMBER]);
				
				scoretype = SCORETYPE_HIT;
				
				break;	
			}
			case 4:
			{
				add_player_record(attacker, attacknumber, "hit4", 1);
				add_player_record(attacker, attacknumber, "hit", 1);
				
				if( game[RUNNER3RD] > 0 ) {	score++; msg += ({ "“"+setup[attacker]["name"]+"”三壘跑者奔回本壘得分！" }); game[RUNNER3RD] = 0; }	
				if( game[RUNNER2ND] > 0 ) {	score++; msg += ({ "“"+setup[attacker]["name"]+"”二壘跑者奔回本壘得分！" }); game[RUNNER2ND] = 0; }
				if( game[RUNNER1ST] > 0 ) {	score++; msg += ({ "“"+setup[attacker]["name"]+"”一壘跑者奔回本壘得分！" }); game[RUNNER1ST] = 0; }
					
				msg += ({ "“"+setup[attacker]["name"]+"”打者奔回本壘得分！" });
				score++;
	
				scoretype = SCORETYPE_HOMERUN;
				
				break;
			}
		}
		
		msg += new_score(gameindex, attacker, defender, score, scoretype);
			
		if( !games[gameindex] )
			return msg;
	}
	else if( basetype == BASETYPE_BALL ) // 保送進壘
	{
		add_player_record(defender, 0, "fourball", 1);
		add_player_record(attacker, attacknumber, "walk", 1);

		// 若一壘有人
		if( game[RUNNER1ST] > 0 )
		{
			// 若二壘也有人
			if( game[RUNNER2ND] > 0 )
			{
				// 若三壘也有人
				if( game[RUNNER3RD] > 0 )
				{
					msg += ({ "“"+setup[attacker]["name"]+"”三壘跑者毫不費力地走回本壘得分！" });
					msg += new_score(gameindex, attacker, defender, 1, SCORETYPE_FOURBALL);
					
					if( !games[gameindex] )
						return msg;
				}

				game[RUNNER3RD] = game[RUNNER2ND];	
			}

			game[RUNNER2ND] = game[RUNNER1ST];
		}

		game[RUNNER1ST] = attacknumber;	
	}

	// 輪下一棒
	if( attacker == game[TEAM1] )
		game[TEAM1NUMBER] = 1 + (game[TEAM1NUMBER] % 9);
	else
		game[TEAM2NUMBER] = 1 + (game[TEAM2NUMBER] % 9);

	setup[attacker]["hint"] = 0;
	setup[defender]["hint"] = 0;
	
	if( game[RUNNER3RD] > 0 || game[RUNNER2ND] > 0 || game[RUNNER1ST] > 0 )
		msg += ({ "“"+setup[attacker]["name"]+"”目前壘上的跑者情形為 [ "+(game[RUNNER3RD] > 0?HIW"○"NOR:WHT"╳"NOR)+" "+(game[RUNNER2ND] > 0?HIW"○"NOR:WHT"╳"NOR)+" "+(game[RUNNER1ST] > 0?HIW"○"NOR:WHT"╳"NOR)+" ] "HIW+game[OUT]+NOR WHT"out"NOR });
		
	games[gameindex] = game;

	return msg;
}

private void check_cache(object player)
{
	if( query_temp("baseballcache/handside/time", player) < time() - 300 )
	{
		int type;
		int level;
		
		if( (level = player->query_skill_level("twohands")) > 0 )
			type = HANDSIDE_TWOHANDS;
		else if( (level = player->query_skill_level("lefthand")) > 0 )
			type = HANDSIDE_LEFTHAND;
		else if( (level = player->query_skill_level("righthand")) > 0 )
			type = HANDSIDE_RIGHTHAND;
		else
			type = HANDSIDE_NONE;
			
		set_temp("baseballcache/handside", ([ "time":time(), "type":type, "level":level ]), player);
	}
}

int get_handside_type(object player)
{
	check_cache(player);
	return query_temp("baseballcache/handside/type", player);
}

int get_handside_level(object player)
{
	check_cache(player);
	return query_temp("baseballcache/handside/level", player);
}

// 打者與投手左右方的差異 (-60~70) 之間
int get_handside_diff(object pitcher, object batter)
{
	int base_level_diff = (get_handside_level(batter) - get_handside_level(pitcher))/20;
	int batter_handside_type = get_handside_type(batter);
	int pitcher_handside_type = get_handside_type(pitcher);
	
	if( pitcher_handside_type == HANDSIDE_NONE )
		return 20 + base_level_diff;
	else if( batter_handside_type == HANDSIDE_TWOHANDS )
		return 8 + base_level_diff;
	else if( batter_handside_type != pitcher_handside_type )
		return 20 + base_level_diff;
	else
		return -10 + base_level_diff;
}

// 取得打擊率
varargs float get_hit_rate(string teamid, int num, int year)
{
	int hit, ab;
	
	if( undefinedp(year) )
		year = season_year;

	if( undefinedp(setup[teamid]) || !mapp(setup[teamid]["roster"][num]) )
		return 0.;

	hit = get_record(RECORD_PLAYER, setup[teamid]["roster"][num]["file"], "hit", year);
	ab = get_record(RECORD_PLAYER, setup[teamid]["roster"][num]["file"], "ab", year);

	if( !hit || !ab ) return 0.;
		
	return 10. * hit / ab;
}

// 進行球賽
void play_game()
{
	string *msg;
	mapping attacksetup, defendsetup;
	string attackteamname, defendteamname;
	int attacknumber, defendnumber;
	string attacker, defender;
	string team1, team2;
	mapping game;
	
	games -= ({ 0 });

	for(int gameindex=0;gameindex<sizeof(games);++gameindex)
	{
		msg = allocate(0);

		game = games[gameindex];
			
		if( ++game[TICK] < PREPARETIME ) continue;

		if( post_season_start && post_season_level )
		{
			if( (game[TICK]+gameindex) % POSTSEASON_TICKTIME ) continue;
		}
		else if( (game[TICK]+gameindex) % TICKTIME ) continue;

		team1 = game[TEAM1];
		team2 = game[TEAM2];
	
		if( !setup[team1] || !setup[team2] ) continue;

		if( !valid_setup(team1) )
		{
			broadcast(HIG"【棒賽】"NOR"“"+setup[team1]["name"]+"”的球隊資料不完整，中止比賽。\n", game);
			cancel_game(team1, 1);
			continue;
		}
			
		if( !valid_setup(team2) )
		{
			broadcast(HIG"【棒賽】"NOR"“"+setup[team2]["name"]+"”的球隊資料不完整，中止比賽。\n", game);
			cancel_game(team2, 1);
			continue;
		}
		
		if( game[TICK] <= PREPARETIME + TICKTIME && game[TICK] >= PREPARETIME )
		{
			setup[team1]["status"] = STATUS_PLAYING;
			setup[team2]["status"] = STATUS_PLAYING;
		}
		
		if( (game[INNING] % 2) > 0 )
		{	
			attacksetup = setup[team2];
			defendsetup = setup[team1];
			
			attacknumber = game[TEAM2NUMBER];
			defendnumber = game[TEAM1NUMBER];
			
			attacker = team2;
			defender = team1;
		}
		else
		{
			attacksetup = setup[team1];
			defendsetup = setup[team2];
			
			attacknumber = game[TEAM1NUMBER];
			defendnumber = game[TEAM2NUMBER];
			
			attacker = team1;
			defender = team2;
		}

		attackteamname = "“"+attacksetup["name"]+"”";
		defendteamname = "“"+defendsetup["name"]+"”";
		
		if( game[INNING] == 0 )
		{
			string defendhandside, attackhandside;
			
			switch(get_handside_type(defendsetup["roster"][0]["object"]))
			{
				case HANDSIDE_NONE: defendhandside = ""; break;
				case HANDSIDE_LEFTHAND: defendhandside = HIC"左"NOR CYN"投"NOR; break;
				case HANDSIDE_RIGHTHAND: defendhandside = HIG"右"NOR GRN"投"NOR; break;
				default: defendhandside = HIR"錯誤"NOR; break;
			}
			switch(get_handside_type(attacksetup["roster"][0]["object"]))
			{
				case HANDSIDE_NONE: attackhandside = ""; break;
				case HANDSIDE_LEFTHAND: attackhandside = HIC"左"NOR CYN"投"NOR; break;
				case HANDSIDE_RIGHTHAND: attackhandside = HIG"右"NOR GRN"投"NOR; break;
				default: attackhandside = HIR"錯誤"NOR; break;
			}
			
			msg += ({ attacksetup["username"]+"的"+attackteamname+"與"+defendsetup["username"]+"的"+defendteamname+"比賽正式開始。" });
			msg += ({ "雙方派出的先發投手分別為"+attackteamname+attackhandside+attacksetup["roster"][0]["object"]->query_idname()+"與"+defendteamname+defendhandside+defendsetup["roster"][0]["object"]->query_idname()+"。" });
			
			game[INNING]++;
		}
		else
		{
			object pitcher = defendsetup["roster"][0]["object"];
			object batter = attacksetup["roster"][attacknumber]["object"];
			
			string defend_msg="", attack_msg="", info_msg="", *special_msg = allocate(0);
			string pitcherballtype;
			
			int pitcherbase = get_handside_level(pitcher) + pitcher->query_str() * 2;		// 投手基本能力(預估範圍 10~1500 之間)
			int batterbase = get_handside_level(batter) + batter->query_str() * 2;			// 打者基本能力(預估範圍 10~1500 之間)
			
			string *availableballtypes;
			int pitchballpower;
			int pitchballspeed;
			int pitchswingeffect = 0;
			int pitchhiteffect = 0;
			int pitchgoodhiteffect = 0;
			
			availableballtypes = filter_array(pitch_ball_types, (: $(pitcher)->query_skill_level($1) > 0 :));
			
			
				
			if( sizeof(availableballtypes) )
			{
				string balltype = availableballtypes[random(sizeof(availableballtypes))];
				
				pitchballpower = pitcher->query_skill_level(balltype);
				pitcherballtype = pitch_ball_types_name[balltype];
				
				switch(balltype)
				{
					case "fourseam":
						pitchballspeed = calculate(pitchballpower, 0.8, 999, 120, 157) + random(6); 
						pitchswingeffect = -20;
						pitchhiteffect = 10;
						pitchgoodhiteffect = 10;
						break;
					case "twoseam":
						pitchballspeed = calculate(pitchballpower, 0.8, 999, 115, 151) + random(6);
						pitchswingeffect = -10;
						pitchhiteffect = 0;
						pitchgoodhiteffect = 10;
						break;
					case "curveball":
						pitchballspeed = calculate(pitchballpower, 0.8, 999, 90, 127) + random(6);
						pitchswingeffect = 10;
						pitchhiteffect = -15;
						pitchgoodhiteffect = 5;
						break;
					case "slider":
						pitchballspeed = calculate(pitchballpower, 0.8, 999, 110, 148) + random(6);
						pitchswingeffect = -5;
						pitchhiteffect = 10;
						pitchgoodhiteffect = -5;
						break;
					case "forkball":
						pitchballspeed = calculate(pitchballpower, 0.8, 999, 100, 137) + random(6);
						pitchswingeffect = 0;
						pitchhiteffect = -10;
						pitchgoodhiteffect = 10;
						break;
					case "sinker":
						pitchballspeed = calculate(pitchballpower, 0.8, 999, 110, 148) + random(6);
						pitchswingeffect = 5;
						pitchhiteffect = 20;
						pitchgoodhiteffect = -25;
						break;
				}
				
				// 球種愈多，威力愈強
				if( sizeof(availableballtypes) == 1 )
					pitchballpower -= 200;
				else
					pitchballpower += sizeof(availableballtypes) * 30;
			}
			else
			{
				pitchballpower = 0;
				pitcherballtype = "軟弱直球";
				
				pitchballspeed = 100+random(15);
			}
			
			pitchballpower += defendsetup["roster"][0][BUFF_PITCHER_POWER];
			
			if( pitchballpower <= 0 )
				pitchballpower = 0;
				
			pitchballpower = calculate(pitchballpower, 0.8, 999, 0, 100);
			
			if( objectp(find_player(defender)) )
			switch(get_handside_type(pitcher))
			{
				case HANDSIDE_LEFTHAND: pitcher->add_skill_exp("lefthand", random(100)); break;
				case HANDSIDE_RIGHTHAND: pitcher->add_skill_exp("righthand", random(100)); break;
			}
			
			if( objectp(find_player(attacker)) )
			switch(get_handside_type(batter))
			{
				case HANDSIDE_LEFTHAND: batter->add_skill_exp("lefthand", random(900)); break;
				case HANDSIDE_RIGHTHAND: batter->add_skill_exp("righthand", random(900)); break;
				case HANDSIDE_TWOHANDS: batter->add_skill_exp("twohands", random(900)); break;
			}
			
			if( defendsetup["hint"] == HINTTYPE_PITCHER )
			{
				pitchballpower += 70;
				pitchballspeed += range_random(2, 5);
				
				defend_msg = defendteamname+pitcher->query_idname()+HIY"全神"NOR YEL"貫注"NOR+(pitchballspeed>=155?"飆":"投")+"出"+(pitchballspeed>=160?"驚人的":"")+" "+pitchballspeed+"km "+ pitcherballtype;
			}
			else
			{
				defend_msg = defendteamname+pitcher->query_idname()+(pitchballspeed>=155?"飆":"投")+"出"+(pitchballspeed>=160?"驚人的":"")+" "+pitchballspeed+"km "+ pitcherballtype;
			}

			
			attack_msg = attackteamname+attacknumber+" 棒"+batter->query_idname();
			
			// 敬遠四壞
			if( defendsetup["hint"] == HINTTYPE_WALK )
			{
				if( ++game[BALL] == 4 )
				{
					defend_msg = defendteamname+pitcher->query_idname()+"往一旁輕輕拋球給捕手，"HIG"壞球"NOR"！引來觀眾一陣噓聲";
					attack_msg += "獲得敬遠四壞保送上壘。";
	
					// 進一壘
					special_msg += new_base(gameindex, attacker, defender, 1, BASETYPE_BALL);
				}
				else
				{
					defend_msg = defendteamname+pitcher->query_idname()+"往一旁輕輕拋球給捕手，"HIG"壞球"NOR"！引來觀眾一陣噓聲";
					attack_msg += "耐心地等待四壞保送";
	
					info_msg = " "HIR+game[STRIKE]+NOR" "HIG+game[BALL]+" "HIW+game[OUT]+NOR;
				}				
			}
			// 進行觸擊短打
			else if( attacksetup["hint"] == HINTTYPE_BUNT )
			{
				// 內野安打!
				if( random(batter->query_int()) > random(600) )
				{
					attack_msg += "擺出奇襲短棒將球擊出！這是一支內野安打！！";
					
					special_msg += new_base(gameindex, attacker, defender, 1, BASETYPE_HIT);
				}
				else if( !random(5) )
				{
					attack_msg += "擺出短棒將球擊出！但卻碰出一顆軟弱飛球被接殺！";
					
					info_msg = " "HIW+(game[OUT]+1)+NOR WHT"out"NOR;
					
					special_msg += new_out(gameindex, attacker, defender, 1, BASETYPE_CATCHKILL);
				}
				else
				{
					// 滿壘
					if( game[RUNNER1ST] > 0 && game[RUNNER2ND] > 0 && game[RUNNER3RD] > 0 )
					{
						if( game[OUT] < 2 )								
							attack_msg += "擺出短棒將球擊出！三壘跑者被封殺在本壘！";
						else
							attack_msg += "擺出短棒將球擊出！但被內野手攔住並刺殺在一壘！";
					}
					else
						attack_msg += "擺出短棒將球擊出！但被內野手攔住並刺殺在一壘！";
													
					info_msg = " "HIW+(game[OUT]+1)+NOR WHT"out"NOR;
					
					special_msg += new_out(gameindex, attacker, defender, 1, BASETYPE_BUNT);
				}
			}
			// 投出好球
			else if( calculate(pitcherbase, 0.8, 1500, 400, 700) > random(1000) )
			{
				// 打者精準選球且出棒的機率 550 + (0~100) + (-60~70) - (0~100) + (-20~5)
				int swingchance = 550 + calculate(batter->query_skill_level("hitaccuracy"), 0.8, 999, 0, 100) + get_handside_diff(pitcher, batter) - pitchballpower + pitchswingeffect;
								
				if( attacksetup["hint"] == HINTTYPE_BATTER )
				{
					attack_msg += HIY"全神"NOR YEL"貫注"NOR;
					swingchance += 40;
				}

				defend_msg += HIR"好球"NOR"！";

				if( game[TEAM1SCORE] > game[TEAM2SCORE] && game[TEAM2] == attacker )
					swingchance += 3 * (game[TEAM1SCORE] - game[TEAM2SCORE]);

				if( game[TEAM2SCORE] > game[TEAM1SCORE] && game[TEAM1] == attacker )
					swingchance += 3 * (game[TEAM2SCORE] - game[TEAM1SCORE]);
						
				// 好球且出棒
				if( swingchance > random(1000) )
				{
					// 擊出球的機率 700 + (0~100) - (0~100)
					int hitchance = 700 + calculate(batter->query_skill_level("hitrange"), 0.7, 999, 0, 100) - pitchballpower;
						
					if( attacksetup["hint"] == HINTTYPE_BATTER )
						hitchance += 40;
					
					if( game[INNING] > 18 )
						hitchance += 3 * (game[INNING]/2-9);
								
					hitchance += attacksetup["roster"][attacknumber][BUFF_BATTER_POWER];
		
					switch(attacknumber)
					{
						case 1: hitchance += 50; break;
						case 2: hitchance += 20; break;
						case 3: hitchance += 40; break;
						case 4: hitchance += 80; break;
						case 5: hitchance += 40; break;
						case 6: hitchance += 10;break;
						case 7: hitchance -= 10; break;
						case 8: hitchance -= 10; break;
						case 9: hitchance -= 10; break;
					}
							
					// 打擊出去
					if( hitchance + pitchhiteffect > random(1000) )
					{
						//tell(find_player("clode"), attacker+(hitchance + pitchgoodhiteffect)+"/"+defender+(defendsetup["outfield"]+defendsetup["infield"])+"\n");
						
						// 安打
						if( hitchance + pitchgoodhiteffect + 100 > random(800 + defendsetup["outfield"] + defendsetup["infield"] ) )
						{												
							// 擊出球的速度(500~3300)
							int hitpower = batter->query_skill_level("hitpower");
							int ballspeed = 500 + hitpower + batterbase;
							
							ballspeed = calculate(ballspeed, 0.7, 3000, 0, 1000);

							// 全壘打
							if( ballspeed > random(8000) )
							{
								int distance;
								
								// 進壘
								special_msg += new_base(gameindex, attacker, defender, 4, BASETYPE_HIT);
								
								if( hitpower > random(5000) )
								{
									if( hitpower > random(5000) )
									{
										if( hitpower > random(5000) )
											distance = range_random(180, 190);
										else
											distance = range_random(170, 180);
									}
									else
										distance = range_random(160, 170);
										
									attack_msg += "轟出了一隻超大號"+( game[RUNNER1ST] > 0 && game[RUNNER2ND] > 0 && game[RUNNER3RD] > 0 ? "滿貫" : "" )+"全壘打("+distance+"m)！！";
								}
								else
								{
									distance = range_random(140, 160);
									attack_msg += "擊出"+( game[RUNNER1ST] > 0 && game[RUNNER2ND] > 0 && game[RUNNER3RD] > 0 ? "滿貫" : "" )+"全壘打("+distance+"m)！！";
								}
								
								if( distance > record[season_year][RECORD_SPECIAL]["maxhomerundistance"] )
								{
									record[season_year][RECORD_SPECIAL]["maxhomerundistance"] = distance;
									record[season_year][RECORD_SPECIAL]["maxhomerundistanceplayer"] = attacksetup["roster"][attacknumber]["file"];
									
									CHANNEL_D->channel_broadcast("sport", HIY"紀錄"NOR YEL"更新 "NOR+attackteamname+"的"+batter->query_idname()+"擊出本季最大號全壘打，距離來到 "HIY+distance+NOR YEL"m"NOR" ！！" );
								}
								
								attack_msg += "("HIY+get_record(RECORD_PLAYER, attacksetup["roster"][attacknumber]["file"], "hit4", season_year)+NOR")";
							}
							// 三壘打
							else if( ballspeed > random(10000) )
							{
								// 進壘
								special_msg += new_base(gameindex, attacker, defender, 3, BASETYPE_HIT);
								
								if( random(defendsetup["outfield"]) < 100 )
									attack_msg += "擊出高遠飛球，外野手奮力撲球仍然慢了一步，形成三壘安打！("HIG+sprintf("%.2f", get_hit_rate(attacker, attacknumber))+NOR")";
								else
									attack_msg += "擊出三壘安打！("HIG+sprintf("%.2f", get_hit_rate(attacker, attacknumber))+NOR")";
							}
							// 二壘打
							else if( ballspeed > random(3000) )
							{
								// 進壘
								special_msg += new_base(gameindex, attacker, defender, 2, BASETYPE_HIT);
								
								if( random(defendsetup["outfield"]) < 100 )
									attack_msg += "擊出不營養飛球但外野手跚跚來遲，形成二壘安打！("HIG+sprintf("%.2f", get_hit_rate(attacker, attacknumber))+NOR")";
								else
									attack_msg += "擊出二壘安打！("HIG+sprintf("%.2f", get_hit_rate(attacker, attacknumber))+NOR")";
							}
							// 一壘打
							else
							{
								// 進壘
								special_msg += new_base(gameindex, attacker, defender, 1, BASETYPE_HIT);
								
								if( random(defendsetup["infield"]) < 100 )
									attack_msg += "擊出的滾地球硬是從內野防線中穿越出去，形成一壘安打！("HIG+sprintf("%.2f", get_hit_rate(attacker, attacknumber))+NOR")";
								else
									attack_msg += "擊出一壘安打！("HIG+sprintf("%.2f", get_hit_rate(attacker, attacknumber))+NOR")";
							}								
						}
						// 界外球
						else if( hitchance > random(5000) )
						{
							if( game[STRIKE] < 2 )
							{
								attack_msg += "擊成界外球";

								game[STRIKE]++;

								info_msg = " "HIR+game[STRIKE]+NOR" "HIG+game[BALL]+" "HIW+game[OUT]+NOR;
							}
							else
							{
								attack_msg += "擊成界外球";

								info_msg = " "HIR+game[STRIKE]+NOR" "HIG+game[BALL]+" "HIW+game[OUT]+NOR;
							}
						}
						// 打擊出去遭接殺或刺殺
						else
						{						
							// 飛球
							if( random(2) )
							{
								attack_msg += "將球遠遠打擊出去！但被接殺";
								
								info_msg = " "HIW+(game[OUT]+1)+NOR WHT"out"NOR;
									
								special_msg += new_out(gameindex, attacker, defender, 1, BASETYPE_CATCHKILL);
							}
							// 滾地
							else
							{
								if( !random(15) && game[RUNNER2ND] > 0 && game[RUNNER1ST] > 0 && game[OUT] == 0 )
								{
									attack_msg += "將球打擊出去！這是一支罕見的三殺打！！";
									
									info_msg = " "HIW+(game[OUT]+3)+NOR WHT"out"NOR;
									
									special_msg += new_out(gameindex, attacker, defender, 3, BASETYPE_TRIPLEPLAY);
								}
								else if( random(2) && game[RUNNER3RD] == 0 && game[RUNNER1ST] > 0 && game[OUT] < 2 )
								{
									attack_msg += "將球打擊出去！這是一支雙殺打！！";
									
									info_msg = " "HIW+(game[OUT]+2)+NOR WHT"out"NOR;
									
									special_msg += new_out(gameindex, attacker, defender, 2, BASETYPE_DOUBLEPLAY);
								}
								else
								{								
									// 滿壘
									if( game[RUNNER1ST] > 0 && game[RUNNER2ND] > 0 && game[RUNNER3RD] > 0 )
									{
										if( game[OUT] < 2 )								
											attack_msg += "將球打擊出去！三壘跑者被封殺在本壘！";
										else
											attack_msg += "將球打擊出去！但被內野手攔住並刺殺在一壘！";
									}
									else
										attack_msg += "將球打擊出去！但被內野手攔住並刺殺在一壘！";
									
									info_msg = " "HIW+(game[OUT]+1)+NOR WHT"out"NOR;
									
									special_msg += new_out(gameindex, attacker, defender, 1, BASETYPE_TOUCHKILL);
								}
							}
						}

					}
					// 揮棒落空
					else
					{
						if( ++game[STRIKE] == 3 )
						{							
							defender == game[TEAM1] ? game[TEAM1K]++ : game[TEAM2K]++;

							attack_msg += "揮棒落空遭到三振出局";

							info_msg = " "HIW+(game[OUT]+1)+NOR WHT"out "HIY + (defender == game[TEAM1] ? game[TEAM1K] : game[TEAM2K]) +NOR YEL"K!"NOR;

							special_msg += new_out(gameindex, attacker, defender, 1, BASETYPE_STRIKEOUT);
						}
						else
						{
							attack_msg += "揮棒落空";	

							info_msg = " "HIR+game[STRIKE]+NOR" "HIG+game[BALL]+" "HIW+game[OUT]+NOR;
						}
					}	
				}
				// 好球未出棒
				else
				{
					if( ++game[STRIKE] == 3 )
					{					
						defender == game[TEAM1] ? game[TEAM1K]++ : game[TEAM2K]++;

						attack_msg += "站着發呆遭到三振出局";

						info_msg = " "HIW+(game[OUT]+1)+NOR WHT"out "HIY + (defender == game[TEAM1] ? game[TEAM1K] : game[TEAM2K]) +NOR YEL"K!"NOR;

						special_msg += new_out(gameindex, attacker, defender, 1, BASETYPE_STRIKEOUT);
					}
					else
					{
						attack_msg += "站着發呆";

						info_msg = " "HIR+game[STRIKE]+NOR" "HIG+game[BALL]+" "HIW+game[OUT]+NOR;
					}
				}
			}
			// 投出壞球
			else
			{
				// 打者看準壞球且不出棒的機率 750 + (0~100) + (-60~70)
				int swingchance = 750 + calculate(batter->query_skill_level("hitaccuracy"), 0.8, 999, 0, 100) + get_handside_diff(pitcher, batter) + pitchswingeffect;

				if( setup[attacker]["hint"] == HINTTYPE_BATTER )
				{
					attack_msg += HIY"全神"NOR YEL"貫注"NOR;
					swingchance += 50;
				}

				if( game[TEAM1SCORE] > game[TEAM2SCORE] && game[TEAM2] == attacker )
					swingchance += 3 * (game[TEAM1SCORE] - game[TEAM2SCORE]);

				if( game[TEAM2SCORE] > game[TEAM1SCORE] && game[TEAM1] == attacker )
					swingchance += 3 * (game[TEAM2SCORE] - game[TEAM1SCORE]);

				defend_msg += HIG"壞球"NOR"，";

				// 壞球且沒出棒
				if( swingchance > random(1000) )
				{
					if( random(200 + pitcherbase) < 5 )
					{
							attack_msg += "被暴投球擊中！獲得觸身保送上壘";

							// 進一壘
							special_msg += new_base(gameindex, attacker, defender, 1, BASETYPE_BALL);
					}
					else
					{
						if( ++game[BALL] == 4 )
						{
							attack_msg += "忍住沒有揮棒，獲得保送上壘";

							// 進一壘
							special_msg += new_base(gameindex, attacker, defender, 1, BASETYPE_BALL);
						}
						else
						{
							attack_msg += "忍住沒有揮棒";

							info_msg = " "HIR+game[STRIKE]+NOR" "HIG+game[BALL]+" "HIW+game[OUT]+NOR;
						}
					}
				}
				// 壞球但有出棒
				else
				{
					if( 200 + pitchballpower > random(800) )
					{
						if( ++game[STRIKE] == 3 )
						{						
							defender == game[TEAM1] ? game[TEAM1K]++ : game[TEAM2K]++;

							attack_msg += "揮棒落空遭到三振出局";

							info_msg = " "HIW+(game[OUT]+1)+NOR WHT"out "HIY + (defender == game[TEAM1] ? game[TEAM1K] : game[TEAM2K]) +NOR YEL"K!"NOR;

							special_msg += new_out(gameindex, attacker, defender, 1, BASETYPE_STRIKEOUT);	
						}
						else
						{
							attack_msg += "大力一揮，揮棒落空";

							info_msg = " "HIR+game[STRIKE]+NOR" "HIG+game[BALL]+" "HIW+game[OUT]+NOR;
						}
					}
					else
					{
						// 飛球
						if( random(2) )
						{						
							attack_msg += "將球遠遠打擊出去！但被接殺";

							info_msg = " "HIW+(game[OUT]+1)+NOR WHT"out"NOR;

							special_msg += new_out(gameindex, attacker, defender, 1, BASETYPE_CATCHKILL);
						}
						// 滾地
						else
						{
							if( !random(15) && game[RUNNER2ND] > 0 && game[RUNNER1ST] > 0 && game[OUT] == 0 )
							{
								attack_msg += "將球打擊出去！這是一支罕見的三殺打！！";

								info_msg = " "HIW+(game[OUT]+3)+NOR WHT"out"NOR;

								special_msg += new_out(gameindex, attacker, defender, 3, BASETYPE_TRIPLEPLAY);
							}
							else if( random(2) && game[RUNNER3RD] == 0 && game[RUNNER1ST] > 0 && game[OUT] <= 1 )
							{
								attack_msg += "將球打擊出去！這是一支雙殺打！！";

								info_msg = " "HIW+(game[OUT]+2)+NOR WHT"out"NOR;

								special_msg += new_out(gameindex, attacker, defender, 2, BASETYPE_DOUBLEPLAY);
							}
							else
							{
								// 滿壘
								if( game[RUNNER1ST] > 0 && game[RUNNER2ND] > 0 && game[RUNNER3RD] > 0 )
								{
									if( game[OUT] < 2 )								
										attack_msg += "將球打擊出去！三壘跑者被封殺在本壘！";
									else
										attack_msg += "將球打擊出去！但被內野手攔住並刺殺在一壘！";
								}
								else
									attack_msg += "將球打擊出去！但被內野手攔住並刺殺在一壘！";

								info_msg = " "HIW+(game[OUT]+1)+NOR WHT"out"NOR;

								special_msg += new_out(gameindex, attacker, defender, 1, BASETYPE_TOUCHKILL);
							}
						}
					}
				}
			}

			if( !game ) continue;

			msg += ({ defend_msg+attack_msg+info_msg });
			
			if( sizeof(special_msg) > 0 )
				msg += special_msg;
		}

		if( sizeof(attacksetup["messages"]) )
		{
			msg = attacksetup["messages"] + msg;
			attacksetup["messages"] = 0;
		}

		if( sizeof(defendsetup["messages"]) )
		{
			msg = defendsetup["messages"] + msg;
			defendsetup["messages"] = 0;
		}
				
		if( sizeof(msg) )
		{
			foreach(string m in msg)
			{
				broadcast(m, game);
			}
		}
	}
}

// 新球賽準備開始, 前者為主場, 後者為客場
void new_game(string id1, string id2)
{
	mapping game = allocate_mapping(0);
	object user;
	
	game[TEAM1] = id1;
	game[TEAM2] = id2;
	game[TEAM1NUMBER] = 1;
	game[TEAM2NUMBER] = 1;
	
	if( post_season_start && post_season_level )
	{
		if( objectp(find_player(id1)) )
			tell(find_player(id1), "\a");
		
		if( objectp(find_player(id2)) )
			tell(find_player(id2), "\a");
			
		game[TICK] = PREPARETIME*4/5 - random(POSTSEASON_TICKTIME);
		
	}
	else
		game[TICK] = random(TICKTIME);

	games += ({ game });

	setup[id1]["status"] = STATUS_PREPARING;
	setup[id2]["status"] = STATUS_PREPARING;

	if( post_season_start && post_season_level )
	{
		setup[id1]["hinttimes"] = HINTTIMES * 2;
		setup[id2]["hinttimes"] = HINTTIMES * 2;
	}
	else
	{
		setup[id1]["hinttimes"] = HINTTIMES;
		setup[id2]["hinttimes"] = HINTTIMES;
	}

	setup[id1]["opponents"] -= ({ id2 });
	setup[id2]["opponents"] -= ({ id1 });
	
	if( objectp(user = find_player(id1)) )
		tell(user, pnoun(2, user)+"的棒球隊伍即將與"+setup[id2]["username"]+"的“"+setup[id2]["name"]+"”進行比賽。\n");
	
	if( objectp(user = find_player(id2)) )
		tell(user, pnoun(2, user)+"的棒球隊伍即將與"+setup[id1]["username"]+"的“"+setup[id1]["name"]+"”進行比賽。\n");
}

void start_game(string id)
{
	foreach(mapping ref game in games)
	{
		if( game[TEAM1] == id || game[TEAM2] == id )
		{
			if( game[TICK] < PREPARETIME )
				game[TICK] = PREPARETIME - 1 - random(TICKTIME);
		}
	}
}

string query_opponent(string id)
{
	foreach(mapping game in games)
	{
		if( !mapp(game) ) continue;

		if( game[TEAM1] == id )
			return game[TEAM2];
		if( game[TEAM2] == id )
			return game[TEAM1];
	}
	
	return 0;
}

varargs mixed query_game(string id)
{
	if( undefinedp(id) ) 
		return games;

	foreach(mapping game in games)
	{
		if( !mapp(game) ) continue;

		if( game[TEAM1] == id || game[TEAM2] == id )
			return game;
	}
	
	return 0;
}

string *query_season()
{
	return season;
}

varargs mapping query_setup(string id)
{
	if( undefinedp(id) )
		return setup;
	else
	{
		// 初始化設定
		if( undefinedp(setup[id]) )
		{
			setup[id] = allocate_mapping(0);
			setup[id]["listener"] = ({ id });
			setup[id]["roster"] = allocate(10);
		}

		return setup[id];
	}
}

int exists(string id)
{
	return !undefinedp(setup[id]);
}

// 重新設定所有球隊的對手
void reset_all_opponents()
{
	foreach(string id, mapping data in setup)
		setup[id]["opponents"] = copy(sort_array(season, (: random(2) ? 1 : -1 :))) - ({ id });	
}

int is_playing(object labor)
{
	string id = query("boss", labor);
	string file = base_name(labor);

	if( undefinedp(setup[id]) ) return 0;

	if( setup[id]["status"] != STATUS_PLAYING ) return 0;

	for(int i=0;i<10;++i)
		if( setup[id]["roster"][i]["file"] == file )
			return 1;

	return 0;
}

mapping query_record()
{
	return record;
}

// 心跳函式
void heart_beat()
{
	int *realtime = TIME_D->query_realtime_array();

	if( !(++tick % 1855) ) save();

	if( !post_season_start && realtime[WDAY] == 0 && realtime[HOUR] == 14 )
	{
		CHANNEL_D->channel_broadcast("sport", HIR"季後"NOR RED"賽"NOR" 停止季賽配對，目前正在進行的比賽全部結束後第 "HIC+season_year+NOR" 球季季後賽即將開始。");
		post_season_start = 1;	
	}
	
	if( !(tick%10) )
	{
		if( post_season_start )
		{		
			// 尚有比賽進行中
			if( sizeof(games) ) return;
			
			switch(post_season_level)
			{
				// 開始季後賽
				case 0:
				{
					post_season_team_8 = sort_array(filter_array(season, (: valid_setup($1, 1) :)), (: sort_team($1, $2) :))[0..7];
					post_season_team_4 = allocate(0);
					post_season_team_2 = allocate(0);
					post_season_eliminate_teams = allocate(0);

					// 季後賽隊伍不足 8 隊
					if( sizeof(post_season_team_8) != 8 )
					{
						if( realtime[WDAY] == 0 && realtime[HOUR] == 20 )
						{
							CHANNEL_D->channel_broadcast("sport", HIR"季後"NOR RED"賽"NOR" 季後賽隊伍不足八支球隊，宣告此次季後賽取消。");
							post_season_level = 8;
						}
						return;
					}
					
					CHANNEL_D->channel_broadcast("sport", HIR"季後"NOR RED"賽"NOR" 所有正規季賽已經結束，以下選出本球季勝率最高的前八強隊伍進行季後賽。");
					
					for(int i=0;i<sizeof(post_season_team_8);++i)
					{
						if( objectp(find_player(post_season_team_8[i])) )
							tell(find_player(post_season_team_8[i]), "\a");

						CHANNEL_D->channel_broadcast("sport", HIR"季後"NOR RED"賽"NOR" "NOR YEL"第"HIY+(i+1)+NOR YEL"名"NOR"：“"+setup[post_season_team_8[i]]["name"]+"”，由"+setup[post_season_team_8[i]]["username"]+"領軍。");
					}
		
					CHANNEL_D->channel_broadcast("sport", HIR"季後"NOR RED"賽"NOR" 以上八隊勁旅將參加本球季的最終決賽，爭取棒球界最高榮耀“"HIY"世"NOR YEL"界"HIY"冠"NOR YEL"軍"NOR"”。");
					CHANNEL_D->channel_broadcast("sport", HIR"季後"NOR RED"賽"NOR" 季後賽所有賽事皆一戰定勝負，總共 7 場比賽將於運動頻道全世界同步實況轉播。");
					CHANNEL_D->channel_broadcast("sport", HIR"季後"NOR RED"賽"NOR" 季後賽的比賽過程中將可擁有 2 倍的暗號使用次數，同時將擁有 20 倍的票房收入。");
					CHANNEL_D->channel_broadcast("sport", HIR"季後"NOR RED"賽"NOR" 首先進行 "HIC"A 組八強賽"NOR"的是排名第 1 的“"+setup[post_season_team_8[0]]["name"]+"”對上排名第 8 的“"+setup[post_season_team_8[7]]["name"]+"”，比賽將在 2 分鐘後開始。");
				
					post_season_level++;
					new_game(post_season_team_8[0], post_season_team_8[7]);
					
					break;
				}
				case 1:
				{
					CHANNEL_D->channel_broadcast("sport", HIR"季後"NOR RED"賽"NOR" 接着進行 "HIC"B 組八強賽"NOR"的是排名第 2 的“"+setup[post_season_team_8[1]]["name"]+"”對上排名第 7 的“"+setup[post_season_team_8[6]]["name"]+"”，比賽將在 2 分鐘後開始。");
					
					post_season_level++;
					new_game(post_season_team_8[1], post_season_team_8[6]);
					
					break;
				}
				case 2:
				{
					CHANNEL_D->channel_broadcast("sport", HIR"季後"NOR RED"賽"NOR" 接着進行 "HIC"C 組八強賽"NOR"的是排名第 3 的“"+setup[post_season_team_8[2]]["name"]+"”對上排名第 6 的“"+setup[post_season_team_8[5]]["name"]+"”，比賽將在 2 分鐘後開始。");
					
					post_season_level++;
					new_game(post_season_team_8[2], post_season_team_8[5]);
					
					break;
				}
				case 3:
				{
					CHANNEL_D->channel_broadcast("sport", HIR"季後"NOR RED"賽"NOR" 接着進行 "HIC"D 組八強賽"NOR"的是排名第 4 的“"+setup[post_season_team_8[3]]["name"]+"”對上排名第 5 的“"+setup[post_season_team_8[4]]["name"]+"”，比賽將在 2 分鐘後開始。");
					
					post_season_level++;
					new_game(post_season_team_8[3], post_season_team_8[4]);
					
					break;
				}
				case 4:
				{
					CHANNEL_D->channel_broadcast("sport", HIR"季後"NOR RED"賽"NOR" 接着進行"HIY"四強準決賽"NOR"的是 A 組晉級隊伍“"+setup[post_season_team_4[0]]["name"]+"”對上 D 組晉級隊伍“"+setup[post_season_team_4[3]]["name"]+"”，比賽將在 2 分鐘後開始。");
					
					post_season_level++;
					new_game(post_season_team_4[0], post_season_team_4[3]);
					
					break;
				}
				case 5:
				{
					CHANNEL_D->channel_broadcast("sport", HIR"季後"NOR RED"賽"NOR" 接着進行"HIY"四強準決賽"NOR"的是 B 組晉級隊伍“"+setup[post_season_team_4[1]]["name"]+"”對上 C 組晉級隊伍“"+setup[post_season_team_4[2]]["name"]+"”，比賽將在 2 分鐘後開始。");
					
					post_season_level++;
					new_game(post_season_team_4[1], post_season_team_4[2]);
					
					break;
				}
				case 6:
				{
				CHANNEL_D->channel_broadcast("sport", HIR"季後"NOR RED"賽"NOR" 接着進行第 "HIC+season_year+NOR" 球季"HIY"總"NOR YEL"冠軍賽"NOR"的是“"+setup[post_season_team_2[0]]["name"]+"”對上“"+setup[post_season_team_2[1]]["name"]+"”，比賽將在 2 分鐘後開始。");
					
					post_season_level++;
					new_game(post_season_team_2[0], post_season_team_2[1]);
					
					break;
				}
				case 7:
				{
					post_season_level++;
					CHANNEL_D->channel_broadcast("sport", HIR"季後"NOR RED"賽"NOR" 本球季所有季賽與季後賽已經全部結束，我們下一個球季再見！！");
					break;
				}
				case 8:
				{
					post_season_level = 0;
					post_season_start = 0;
					season_year++;
					
					CHANNEL_D->channel_broadcast("sport", HIG"全新"NOR GRN"球季"NOR" 新的第 "HIC+season_year+NOR" 球季開始，所有參賽球隊開始進行比賽配對。");
					
					post_season_team_8 = allocate(0);
					post_season_team_4 = allocate(0);
					post_season_team_2 = allocate(0);
					post_season_eliminate_teams = allocate(0);
					
					record[season_year] = allocate_mapping(0);
					record[season_year][RECORD_TEAM] = allocate_mapping(0);
					record[season_year][RECORD_PLAYER] = allocate_mapping(0);
					record[season_year][RECORD_SPECIAL] = allocate_mapping(0);
		
					reset_all_opponents();
					
					foreach(string id in season)
					{
						setup[id]["keepwins"] = 0;
						setup[id]["keeploses"] = 0;
					}	
			
					save();
					break;	
				}
			}
		}
		else
		{
			// 處理比賽配對
			foreach(string id in season)
			{
				if( undefinedp(setup[id]) ) continue;
		
				// 尋找對手，新的比賽準備開始
				if(setup[id]["status"] == STATUS_IDLE )
				{
					string opponent_id = 0;
		
					// 球隊設定有誤，取消配對
					if( !valid_setup(id, 1) )
					{
						leave_season(id);
						continue;
					}
		
					// 若已無對手，重新列表
					if( !sizeof(setup[id]["opponents"]) )
						setup[id]["opponents"] = copy(sort_array(season, (: random(2) ? 1 : -1 :))) - ({ id });
		
					// 搜尋目前沒有比賽的對手
					foreach(string teamid in setup[id]["opponents"])
					{
						if( setup[teamid]["status"] == STATUS_IDLE )
						{
							if( !valid_setup(teamid, 1) )
							{
								leave_season(teamid);
								continue;
							}
		
							opponent_id = teamid;
							break;
						}
					}
		
					// 找不到對手，等待下次 heartbeat 再重新搜尋
					if( !stringp(opponent_id) )
					{
						// 連續 180 次(40min)找不到對手，重新列表
						if( ++setup[id]["no_opponent"] > 240 )
						{
							setup[id]["no_opponent"] = 0;
							setup[id]["opponents"] = copy(sort_array(season, (: random(2) ? 1 : -1 :))) - ({ id });
						}
						continue;
					}
		
					setup[id]["no_opponent"] = 0;
					setup[opponent_id]["no_opponent"] = 0;
					
					// 隨機決定主客場
					if( !random(2) )
					{
						//CHANNEL_D->channel_broadcast("sport", HIC+"季賽"NOR CYN"配對 "NOR+setup[id]["username"]+"的“"+setup[id]["name"]+"”與"+setup[opponent_id]["username"]+"的“"+setup[opponent_id]["name"]+"”將於 "+(PREPARETIME/60)+" 分鐘後進行球賽。");
						new_game(id, opponent_id);
					}
					else
					{
						//CHANNEL_D->channel_broadcast("sport", HIC+"季賽"NOR CYN"配對 "NOR+setup[opponent_id]["username"]+"的“"+setup[opponent_id]["name"]+"”與"+setup[id]["username"]+"的“"+setup[id]["name"]+"”將於 "+(PREPARETIME/60)+" 分鐘後進行球賽。");
						new_game(opponent_id, id);
					}
				}
			}
		}
	}
	play_game();
}

// 切換即時戰況
void set_listener(string listener_id, string target_team)
{	
	if( !stringp(target_team) )
	{
		foreach(string team, mapping data in setup)
			setup[team]["listener"] -= ({ listener_id });
	}
	else
	{
		setup[target_team]["listener"] |= ({ listener_id });
	}
}

int remove()
{
	return save();
}

void fix_setup()
{
	/*
	foreach(string id, mapping data in setup)
	{

	}
*/
	save();
}

void fix_record()
{

}

int query_season_year()
{
	return season_year;	
}

int is_in_post_season()
{
	return post_season_start && post_season_level;	
}

string *query_post_season_team(int number)
{
	switch(number)
	{
		case 8:
			return post_season_team_8;
			break;
		case 4:
			return post_season_team_4;
			break;
		case 2:
			return post_season_team_2;
			break;
	}
}

string *query_post_season_eliminate_teams()
{
	return post_season_eliminate_teams;
}

void add_message(string id, string message)
{
	if( undefinedp(setup[id]) ) return;	
	
	if( !arrayp(setup[id]["messages"]) )
		setup[id]["messages"] = ({ message });
	else
		setup[id]["messages"] += ({ message });
}

void create()
{
	backup();
	
	if( !restore_object(DATA) )
	{
		setup = allocate_mapping(0);
		season = allocate(0);
		games = allocate(0);
		record = allocate_mapping(0);
		
		save();
	}

	set_heart_beat(1);
}

string query_name()
{
	return "棒球系統(BASEBALL_D)";
}
