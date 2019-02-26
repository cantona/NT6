// eventd.c

#include <ansi.h>
#include <localtime.h>

inherit F_DBASE;

nosave string *event_name;      // 系統中所有的事件
nosave mapping event_list;      // 待觸發的事件

void collect_all_event();

void create()
{
        string event;
        object eob;

        seteuid(ROOT_UID);
        set("channel_id", "事件精靈");
        CHANNEL_D->do_channel(this_object(), "sys", "事件系統已經啟動。");

        event_name = get_dir(EVENT_DIR + "*.c");
        event_name = map_array(event_name, (: $1[0..<3] :));

        // 析構所有的事件
        foreach (event in event_name)
                if (objectp(eob = find_object(EVENT_DIR + event)))
                        destruct(eob);

        event_list = ([ ]);
        collect_all_event();
        set_heart_beat(5);      // 每個小時心跳一次
}

int clean_up()
{
        return 1;
}

string *query_all_event()
{
        return event_name;
}

mapping query_event_list()
{
        return event_list;
}

// EVENT_D啟動時收集所有的事件
void collect_all_event()
{
        string event;

        foreach (event in event_name)
                (EVENT_DIR + event)->create_event();
}

// 登記在某時刻啟動事件
int test(string st, int year, int month, int day, int hour, mixed para)
{
        if (undefinedp(event_list[st]))
                return notify_fail("not found..\n");

        event_list[st] = ({ year, month, day, hour, para });
}

// 登記在某時刻啟動事件
int at_when(int year, int month, int day, int hour, mixed para)
{
        object pob;
        int t;
        mixed *lt;

        if (! objectp(pob = previous_object()))
                return 0;

        if (geteuid(pob) != ROOT_UID)
                // 為了安全，只有具有ROOT身份的對象才能夠登記事件
                return 0;

        event_list[base_name(pob)] = ({ year, month, day, hour, para });
}

// 登記在一段時間以後啟動事件
// 如果傳入的參數是負數，則標誌了一個絕對的時間
// 比如：Y = 0 month = 0 day = 1 hour = -5 表示明天5點鐘
int at_after(int year, int month, int day, int hour, mixed para)
{
        mixed *lt;

        lt = NATURE_D->query_localtime(time());
        if (year < 0)  year = -year;   else year += lt[LT_YEAR];
        if (month < 0) month = -month; else month += lt[LT_MON] + 1;
        if (day < 0)   day = -day;     else day += lt[LT_MDAY];
        if (hour < 0)  hour = -hour;   else hour += lt[LT_HOUR];
        return at_when(year, month, day, hour, para);
}

// 每個小時心跳一次，檢查所有的事件
void heart_beat()
{
        mixed *lt;
        string *ks;
        string event;
        mixed *el;
        int tnow, tt;
        int r;

        lt = NATURE_D->query_localtime(time());
        lt[LT_MON]++;
        tnow = lt[LT_YEAR] * 1000000 +
               lt[LT_MON] * 10000 +
               lt[LT_MDAY] * 100 +
               lt[LT_HOUR];

        ks = keys(event_list);
        foreach (event in ks)
        {
                el = event_list[event];
                tt = el[0] * 1000000 +
                     el[1] * 10000 +
                     el[2] * 100 +
                     el[3];
                if (tnow < tt) continue;

                // 先去掉這個事件 - 這個操作必須在觸發前完成
                map_delete(event_list, event);

                // 事件需要觸發，調用傳入參數
                r = catch(event->trigger_event(el[4],
                                               lt[LT_YEAR], lt[LT_MON],
                                               lt[LT_MON], lt[LT_MDAY]));
                if (r) log_file("static/event", sprintf("%s event:%s trigger occur an error.\n",
                                                        log_time(), ks));
        }
}