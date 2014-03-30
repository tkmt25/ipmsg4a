package jp.tcc.ipmsg4a.model;

import java.util.Arrays;
import java.util.Collections;
import java.util.Date;
import java.util.HashSet;
import java.util.Set;

public class Message implements Comparable<Message>{
	private User source;
	private String message;
	private Set<User> destinations = new HashSet<User>();
	private Date timestamp;
	
	public Message(User source, String message, User... destinations){
		this.source = source;
		this.message = message;
		this.destinations.addAll(Arrays.asList(destinations));
		this.timestamp = new Date();
	}

	public User getSource() {
		return source;
	}

	public String getMessage() {
		return message;
	}
	
	public Date getTimestamp() {
		return timestamp;
	}
	
	public Set<User> getDestinations(){
		return Collections.unmodifiableSet(this.destinations);
	}

	@Override
	public int compareTo(Message another) {
		return this.timestamp.compareTo(another.timestamp);
	}

	
}
