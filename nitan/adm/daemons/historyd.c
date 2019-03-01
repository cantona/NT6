// This program is a part of NT mudlib

#define DATA_PATH       "/data/history.o"

string *history;

int save()
{
	return save_object(DATA_PATH);	
}

int remove()
{
	return save();
}

void add_history(string key, string id, string value)
{
        history = ({ time(), key, id, value }) + history;
	
	save();
}

void remove_history(int index)
{
        history = history[0..((index-1)*4)-1] + history[(index-1)*4+4..];

	save();
}

string *query_history()
{
	return copy(history);
}

void create()
{
	if( !restore_object(DATA_PATH) )
	{
		history = allocate(0);
		save();
	}
}

string query_name()
{
	return "歷史事件系統(HISTORY_D)";
}
