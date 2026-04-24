/// @file      event_system.cpp
/// @namespace Chess
/// @brief     Chess Event System (CES) - Event Management Implementation.
/// @author    Calileus
/// @date      2026-01-22
/// @copyright 2026 Obsidian Honor Coders. Licensed under Apache 2.0.
/// @see       https://github.com/ObsidianHonorCoders/inheritance-chess
/// @details   Implementation of event-driven architecture for chess events.

#include "event_system.h"
#include <algorithm>
#include <iostream>

namespace Chess
{

  size_t ChessEventSystem::subscribe(EventType type, EventListener listener)
  {
    size_t subscription_id = next_subscription_id_++;
    
    // Create subscription
    subscriptions_.emplace_back(subscription_id, type, listener);
    
    // Add to type index
    type_to_subscriptions_[type].push_back(subscription_id);
    
    return subscription_id;
  }

  bool ChessEventSystem::unsubscribe(size_t subscription_id)
  {
    // Find subscription by ID
    auto it = std::find_if(subscriptions_.begin(), subscriptions_.end(),
        [subscription_id](const Subscription& sub) {
            return sub.id == subscription_id;
        });
    
    if (it == subscriptions_.end())
    {
      return false; // Not found
    }
    
    // Remove from type index
    EventType type = it->type;
    auto& type_subs = type_to_subscriptions_[type];
    type_subs.erase(std::remove(type_subs.begin(), type_subs.end(), subscription_id), type_subs.end());
    
    // Remove from main list
    subscriptions_.erase(it);
    
    return true;
  }

  void ChessEventSystem::emit_event(const EventData& event)
  {
    // Find all subscribers for this event type
    auto it = type_to_subscriptions_.find(event.type);
    if (it == type_to_subscriptions_.end())
    {
      return; // No subscribers for this event type
    }
    
    // Notify all subscribers
    for (size_t subscription_id : it->second)
    {
      // Find subscription
      auto sub_it = std::find_if(subscriptions_.begin(), subscriptions_.end(),
          [subscription_id](const Subscription& sub) {
              return sub.id == subscription_id;
          });
      
      if (sub_it != subscriptions_.end())
      {
        try
        {
          sub_it->listener(event);
        }
        catch (const std::exception& e)
        {
          std::cerr << "Event listener error: " << e.what() << std::endl;
        }
      }
    }
  }

  void ChessEventSystem::emit_move_executed(const Grid& grid, const Move& move, Color turn)
  {
    EventData event(EventType::MOVE_EXECUTED, &grid, move, turn);
    emit_event(event);
  }

  void ChessEventSystem::emit_piece_captured(const Grid& grid, const Move& move, Color turn)
  {
    EventData event(EventType::PIECE_CAPTURED, &grid, move, turn);
    emit_event(event);
  }

  void ChessEventSystem::emit_position_updated(const Grid& grid, Color turn)
  {
    Move dummy_move; // Empty move for position updates
    EventData event(EventType::POSITION_UPDATED, &grid, dummy_move, turn);
    emit_event(event);
  }

  void ChessEventSystem::emit_game_started(const Grid& grid)
  {
    Move dummy_move; // Empty move for game start
    EventData event(EventType::GAME_STARTED, &grid, dummy_move, Color::WHITE);
    emit_event(event);
  }

  void ChessEventSystem::emit_game_ended(const Grid& grid, const std::string& reason, Color turn)
  {
    Move dummy_move; // Empty move for game end
    EventData event(EventType::GAME_ENDED, &grid, dummy_move, turn);
    emit_event(event);
    
    // Also emit reason as a separate event for more detailed handling
    std::cout << "Game ended: " << reason << std::endl;
  }

  void ChessEventSystem::emit_turn_changed(const Grid& grid, Color new_turn)
  {
    Move dummy_move; // Empty move for turn change
    EventData event(EventType::TURN_CHANGED, &grid, dummy_move, new_turn);
    emit_event(event);
  }

  void ChessEventSystem::emit_check_detected(const Grid& grid, Color checked_color)
  {
    Move dummy_move; // Empty move for check detection
    EventData event(EventType::CHECK_DETECTED, &grid, dummy_move, checked_color);
    emit_event(event);
  }

  void ChessEventSystem::emit_checkmate_detected(const Grid& grid, Color checkmated_color)
  {
    Move dummy_move; // Empty move for checkmate detection
    EventData event(EventType::CHECKMATE_DETECTED, &grid, dummy_move, checkmated_color);
    emit_event(event);
  }

  void ChessEventSystem::emit_stalemate_detected(const Grid& grid, Color stalemate_color)
  {
    Move dummy_move; // Empty move for stalemate detection
    EventData event(EventType::STALEMATE_DETECTED, &grid, dummy_move, stalemate_color);
    emit_event(event);
  }

  size_t ChessEventSystem::get_subscriber_count() const
  {
    return subscriptions_.size();
  }

  size_t ChessEventSystem::get_subscriber_count(EventType type) const
  {
    auto it = type_to_subscriptions_.find(type);
    return (it != type_to_subscriptions_.end()) ? it->second.size() : 0;
  }

} // namespace Chess
