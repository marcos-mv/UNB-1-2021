package com.gpcoder.publisherconfirm;

import com.rabbitmq.client.*;

import java.io.IOException;
import java.util.concurrent.TimeoutException;

public class BatchPublisherConfirm {

    private static final String EXCHANGE_NAME = "PublishingMessage.DirectExchange";
    private static final String QUEUE_NAME = "PublishingMessage.DirectQueue1";
    private static final String ROUTING_KEY = "batchMessage";
    private static final int NUM_OF_MESSAGE = 6;
    private static final int BATCH_SIZE = 3;

    public static void main(String[] args) throws IOException, TimeoutException, InterruptedException {
        // Create connection
        ConnectionFactory factory = new ConnectionFactory();
        factory.setHost("localhost");
        Connection connection = factory.newConnection();

        // Create channel
        Channel channel = connection.createChannel();

        // Create direct exchange - exchange, builtinExchangeType, durable
        channel.exchangeDeclare(EXCHANGE_NAME, BuiltinExchangeType.DIRECT, true);

        // Create queue - (queueName, durable, exclusive, autoDelete, arguments)
        channel.queueDeclare(QUEUE_NAME, true, false, false, null);

        // Bind queue to exchange - (queue, exchange, routingKey)
        channel.queueBind(QUEUE_NAME, EXCHANGE_NAME, ROUTING_KEY);

        // Enabling Publisher Confirms on a Channel
        AMQP.Confirm.SelectOk confirmed = channel.confirmSelect();
        System.out.println("Enabled published confirm: " + confirmed);

        // Handling Publisher Confirms Asynchronously
        channel.addConfirmListener((sequenceNumber, multiple) -> {
            // code when message is confirmed
            System.out.println("[Confirmed - multiple] " + multiple);
            System.out.println("[Confirmed - sequenceNumber] " + sequenceNumber);
        }, (sequenceNumber, multiple) -> {
            // code when message is nack-ed
            // Message was lost, we just print the info for debug;
            // otherwise, this case should be handled differently
            System.out.println("Not-Acknowledging for message with id " + sequenceNumber);
        });

        // Publish messages to the channel and put the ids to the queue
        for (int i = 1; i <= NUM_OF_MESSAGE; i++) {

            String message = "Message " + i;

            System.out.println("[Send] [" + channel.getNextPublishSeqNo() + "] " + message);

            channel.basicPublish(EXCHANGE_NAME, ROUTING_KEY, null, message.getBytes());

            if (i % BATCH_SIZE == 0) {
                channel.waitForConfirmsOrDie(300); // in ms
            }
        }


        DeliverCallback deliverCallback = (consumerTag, message) -> {
            System.out.println("[Received] : " + new String(message.getBody()));
        };

        CancelCallback cancelCallback = consumerTag -> {
            System.out.println("[Canceled]" + consumerTag);
        };

        // basicConsume - ( queue, autoAck, deliverCallback, cancelCallback)
        channel.basicConsume(QUEUE_NAME, true, deliverCallback, cancelCallback);
    }
}