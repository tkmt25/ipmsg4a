package jp.tcc.ipmsg4a.messenger;

import jp.tcc.ipmsg4a.model.Message;

public interface MessengerListener {
	public void onOpenMessage(Message message);
	public void onSend(Message message);
	public void onReceive(Message message);
}
