//===--- SyntaxFactory.h - Swift Syntax Builder Interface -------*- C++ -*-===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2017 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://swift.org/LICENSE.txt for license information
// See https://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//
//
// This file defines the SyntaxFactory, one of the most important client-facing
// types in lib/Syntax and likely to be very commonly used.
//
// Effectively a namespace, SyntaxFactory is never instantiated, but is *the*
// one-stop shop for making new Syntax nodes. Putting all of these into a
// collection of static methods provides a single point of API lookup for
// clients' convenience and also allows the library to hide all of the
// constructors for all Syntax nodes, as the SyntaxFactory is friend to all.
//
//===----------------------------------------------------------------------===//

#ifndef SWIFT_SYNTAX_SyntaxFactory_H
#define SWIFT_SYNTAX_SyntaxFactory_H

#include "swift/Syntax/DeclSyntax.h"
#include "swift/Syntax/GenericSyntax.h"
#include "swift/Syntax/TokenSyntax.h"
#include "swift/Syntax/TypeSyntax.h"
#include "swift/Syntax/Trivia.h"
#include "llvm/ADT/ArrayRef.h"

#include <vector>

namespace swift {
namespace syntax {

class ArrayTypeSyntax;
class BreakStmtSyntax;
class CodeBlockStmtSyntax;
class DeclMembersSyntax;
class DictionaryTypeSyntax;
class FallthroughStmtSyntax;
class FunctionTypeSyntax;
class GenericParameterSyntax;
class GenericWhereClauseSyntax;
class ImplicitlyUnwrappedOptionalTypeSyntax;
class MetatypeTypeSyntax;
class OptionalTypeSyntax;
class SameTypeRequirementSyntax;
class StmtListSyntax;
class StructDeclSyntax;
class TupleTypeElementSyntax;
class TupleTypeSyntax;
class TypeArgumentListSyntax;
class TypeAttributesSyntax;
class TypeAliasDeclSyntax;
class UnknownSyntax;
struct TokenSyntax;

/// The Syntax builder - the one-stop shop for making new Syntax nodes.
struct SyntaxFactory {
  /// Collect a list of tokens into a piece of "unknown" syntax.
  static UnknownSyntax
  makeUnknownSyntax(llvm::ArrayRef<RC<TokenSyntax>> Tokens);

#pragma mark - Declarations
  /// Make a struct declaration with the specified elements.
  static StructDeclSyntax
  makeStructDecl(RC<TokenSyntax> StructToken, RC<TokenSyntax> Identifier,
                 Syntax GenericParameters, Syntax WhereClause,
                 RC<TokenSyntax> LeftBrace, Syntax DeclMembers,
                 RC<TokenSyntax> RightBrace);

  /// Make a struct declaration with all missing elements.
  static StructDeclSyntax makeBlankStructDecl();

  /// Make a typealias declaration with the specified elements.
  static TypeAliasDeclSyntax
  makeTypealiasDecl(RC<TokenSyntax> TypealiasToken, RC<TokenSyntax> Identifier,
                    GenericParameterClauseSyntax GenericParams,
                    RC<TokenSyntax> AssignmentToken, TypeSyntax Type);

  /// Make a typealias declaration with all missing elements.
  static TypeAliasDeclSyntax makeBlankTypealiasDecl();

  /// Make an empty list of declaration members.
  static DeclMembersSyntax makeBlankDeclMembers();

#pragma mark - Statements

  /// Make a code block with the specified elements.
  static CodeBlockStmtSyntax
  makeCodeBlock(RC<TokenSyntax> LeftBraceToken,
                StmtListSyntax Elements,
                RC<TokenSyntax> RightBraceToken);

  /// Make a code block with all missing elements.
  static CodeBlockStmtSyntax makeBlankCodeBlock();

  /// Make a fallthrough statement with the give `fallthrough` keyword.
  static FallthroughStmtSyntax
  makeFallthroughStmt(RC<TokenSyntax> FallthroughKeyword);

  /// Make a fallthrough statement with the `fallthrough` keyword
  /// marked as missing.
  static FallthroughStmtSyntax makeBlankFallthroughStmt();

  /// Make a break statement with the give `break` keyword and
  /// destination label.
  static BreakStmtSyntax
  makeBreakStmt(RC<TokenSyntax> BreakKeyword, RC<TokenSyntax> Label);

  /// Make a break statement with the `break` keyword
  /// and destination label marked as missing.
  static BreakStmtSyntax makeBlankBreakStmtSyntax();

#pragma mark - Tokens

  /// Make a 'fallthrough' keyword with the specified leading and
  /// trailing trivia.
  static RC<TokenSyntax> makeFallthroughKeyword(const Trivia &LeadingTrivia,
                                                const Trivia &TrailingTrivia);

  /// Make an at-sign '@' token with the specified leading and
  /// trailing trivia.
  static RC<TokenSyntax> makeAtSignToken(const Trivia &LeadingTrivia,
                                         const Trivia &TrailingTrivia);

  /// Make a 'break' keyword with the specified leading and
  /// trailing trivia.
  static RC<TokenSyntax> makeBreakKeyword(const Trivia &LeadingTrivia,
                                          const Trivia &TrailingTrivia);

  /// Make a left angle '<' token with the specified leading and
  /// trailing trivia.
  static RC<TokenSyntax> makeLeftAngleToken(const Trivia &LeadingTrivia,
                                            const Trivia &TrailingTrivia);

  /// Make a right angle '>' token with the specified leading and
  /// trailing trivia.
  static RC<TokenSyntax> makeRightAngleToken(const Trivia &LeadingTrivia,
                                             const Trivia &TrailingTrivia);

  /// Make a left parenthesis '(' token with the specified leading and
  /// trailing trivia.
  static RC<TokenSyntax> makeLeftParenToken(const Trivia &LeadingTrivia,
                                            const Trivia &TrailingTrivia);

  /// Make a right parenthesis ')' token with the specified leading and
  /// trailing trivia.
  static RC<TokenSyntax> makeRightParenToken(const Trivia &LeadingTrivia,
                                            const Trivia &TrailingTrivia);

  /// Make a left square bracket '[' token with the specified leading and
  /// trailing trivia.
  static RC<TokenSyntax>
  makeLeftSquareBracketToken(const Trivia &LeadingTrivia,
                             const Trivia &TrailingTrivia);

  /// Make a right square bracket ']' token with the specified leading and
  /// trailing trivia.
  static RC<TokenSyntax>
  makeRightSquareBracketToken(const Trivia &LeadingTrivia,
                              const Trivia &TrailingTrivia);

  /// Make a postfix question '?' token with the specified trailing trivia.
  /// The leading trivia is assumed to be of zero width.
  static RC<TokenSyntax>
  makeQuestionPostfixToken(const Trivia &TrailingTrivia);

  /// Make an exclamation '!' token with the specified trailing trivia.
  /// The leading trivia is assumed to be of zero width.
  static RC<TokenSyntax> makeExclaimPostfixToken(const Trivia &TrailingTrivia);

  /// Make an identifier token with the specified leading and trailing trivia.
  static RC<TokenSyntax> makeIdentifier(OwnedString Name,
                                        const Trivia &LeadingTrivia,
                                        const Trivia &TrailingTrivia);

  /// Make a comma ',' token with the specified leading and trailing trivia.
  static RC<TokenSyntax> makeCommaToken(const Trivia &LeadingTrivia,
                                        const Trivia &TrailingTrivia);

  /// Make a colon ':' token with the specified leading and trailing trivia.
  static RC<TokenSyntax> makeColonToken(const Trivia &LeadingTrivia,
                                        const Trivia &TrailingTrivia);

  /// Make a dot '.' token with the specified leading and trailing trivia.
  static RC<TokenSyntax> makeDotToken(const Trivia &LeadingTrivia,
                                      const Trivia &TrailingTrivia);

  /// Make a 'struct' keyword with the specified leading and trailing trivia.
  static RC<TokenSyntax> makeStructKeyword(const Trivia &LeadingTrivia,
                                           const Trivia &TrailingTrivia);

  /// Make a 'where' keyword with the specified leading and trailing trivia.
  static RC<TokenSyntax> makeWhereKeyword(const Trivia &LeadingTrivia,
                                          const Trivia &TrailingTrivia);

  /// Make a 'inout' keyword with the specified leading and trailing trivia.
  static RC<TokenSyntax> makeInoutKeyword(const Trivia &LeadingTrivia,
                                          const Trivia &TrailingTrivia);

  /// Make a 'throws' keyword with the specified leading and trailing trivia.
  static RC<TokenSyntax> makeThrowsKeyword(const Trivia &LeadingTrivia,
                                           const Trivia &TrailingTrivia);

  /// Make a 'rethrows' keyword with the specified leading and
  /// trailing trivia.
  static RC<TokenSyntax> makeRethrowsKeyword(const Trivia &LeadingTrivia,
                                             const Trivia &TrailingTrivia);

  /// Make a 'typealias' keyword with the specified leading and
  /// trailing trivia.
  static RC<TokenSyntax> makeTypealiasKeyword(const Trivia &LeadingTrivia,
                                              const Trivia &TrailingTrivia);

  /// Make an equal '=' token with the specified leading and
  /// trailing trivia.
  static RC<TokenSyntax> makeEqualToken(const Trivia &LeadingTrivia,
                                        const Trivia &TrailingTrivia);

  /// Make an arrow '->' token with the specified leading and trailing trivia.
  static RC<TokenSyntax> makeArrow(const Trivia &LeadingTrivia,
                                   const Trivia &TrailingTrivia);

  /// Make an equality '==' binary operator with the specified leading and
  /// trailing trivia.
  static RC<TokenSyntax> makeEqualityOperator(const Trivia &LeadingTrivia,
                                           const Trivia &TrailingTrivia);

  /// Make the terminal identifier token `Type`
  static RC<TokenSyntax> makeTypeToken(const Trivia &LeadingTrivia,
                                       const Trivia &TrailingTrivia);

  /// Make the terminal identifier token `Protocol`
  static RC<TokenSyntax> makeProtocolToken(const Trivia &LeadingTrivia,
                                           const Trivia &TrailingTrivia);

#pragma mark - Types

#pragma mark - type-attribute

  /// Make a type attribute with the specified elements.
  static TypeAttributeSyntax
  makeTypeAttribute(RC<TokenSyntax> AtSignToken,
                    RC<TokenSyntax> Identifier,
                    RC<TokenSyntax> LeftParen,
                    BalancedTokensSyntax BalancedTokens,
                    RC<TokenSyntax> RightParen);

  /// Make a type attribute with all elements marked as missing.
  static TypeAttributeSyntax makeBlankTypeAttribute();

#pragma mark - type-attributes

  /// Make a set of type attributes with all elements marked as missing.
  static TypeAttributesSyntax makeBlankTypeAttributes();

  /// Make a list of balanced tokens.
  static BalancedTokensSyntax
  makeBalancedTokens(RawSyntax::LayoutList Tokens);

  /// Make an empty list of balanced tokens.
  static BalancedTokensSyntax makeBlankBalancedTokens();

  /// Make a non-generic type identifier with some name.
  static TypeIdentifierSyntax
  makeTypeIdentifier(OwnedString Name, const Trivia &LeadingTrivia,
                     const Trivia &TrailingTrivia);

  /// Make a generic type identifier.
  static TypeIdentifierSyntax
  makeTypeIdentifier(RC<TokenSyntax> Identifier,
                     GenericArgumentClauseSyntax GenericArgs);

  /// Make a bare "Any" type.
  static TypeIdentifierSyntax makeAnyTypeIdentifier();

  /// Make a bare "Self" type.
  static TypeIdentifierSyntax makeSelfTypeIdentifier();

  /// Make a bare "()" void tuple type
  static TupleTypeSyntax makeVoidTupleType();

  /// Make a tuple type element of the form 'Name: ElementType'
  static TupleTypeElementSyntax
  makeTupleTypeElement(RC<TokenSyntax> Name, TypeSyntax ElementType);

  /// Make a tuple type element without a label.
  static TupleTypeElementSyntax makeTupleTypeElement(TypeSyntax ElementType);

  /// Make an optional type, such as `Int?`
  static OptionalTypeSyntax
  makeOptionalType(TypeSyntax BaseType, const Trivia &TrailingTrivia);

  /// Make an optional type with all elements marked as missing.
  static OptionalTypeSyntax makeBlankOptionalType();

  /// Make an implicitly unwrapped optional type, such as `Int!`
  static ImplicitlyUnwrappedOptionalTypeSyntax
  makeImplicitlyUnwrappedOptionalType(TypeSyntax BaseType,
                                      const Trivia &TrailingTrivia);

  static ImplicitlyUnwrappedOptionalTypeSyntax
  makeBlankImplicitlyUnwrappedOptionalType();

  /// Make a metatype type, as in `T.Type`
  /// `Type` is a terminal token here, not a placeholder for something else.
  static MetatypeTypeSyntax makeMetatypeType(TypeSyntax BaseType,
                                             RC<TokenSyntax> DotToken,
                                             RC<TokenSyntax> TypeToken);

  /// Make a metatype type with all elements marked as missing.
  static MetatypeTypeSyntax makeBlankMetatypeType();

  /// Make an sugared Array type, as in `[MyType]`.
  static ArrayTypeSyntax makeArrayType(RC<TokenSyntax> LeftSquareBracket,
                                       TypeSyntax ElementType,
                                       RC<TokenSyntax> RightSquareBracket);

  /// Make an array type with all elements marked as missing.
  static ArrayTypeSyntax makeBlankArrayType();

  /// Make a Dictionary type, as in `[Key : Value]`.
  static DictionaryTypeSyntax
  makeDictionaryType(RC<TokenSyntax> LeftSquareBracket, TypeSyntax KeyType,
                     RC<TokenSyntax> Colon, TypeSyntax ValueType,
                     RC<TokenSyntax> RightSquareBracket);

  /// Make an a dictionary type with all elements marked as missing.
  static DictionaryTypeSyntax makeBlankDictionaryType();

  /// Make a function argument type syntax with the specified elements.
  static FunctionTypeArgumentSyntax
  makeFunctionTypeArgument(RC<TokenSyntax> ExternalParameterName,
                           RC<TokenSyntax> LocalParameterName,
                           TypeAttributesSyntax TypeAttributes,
                           RC<TokenSyntax> InoutKeyword,
                           RC<TokenSyntax> ColonToken,
                           TypeSyntax ParameterTypeSyntax);

  /// Make a simple function type argument syntax with the given label and
  /// simple type name.
  static FunctionTypeArgumentSyntax
  makeFunctionTypeArgument(RC<TokenSyntax> LocalParameterName,
                           RC<TokenSyntax> ColonToken,
                           TypeSyntax ParameterType);

  /// Make a simple function type argument syntax with the given simple
  /// type name.
  static FunctionTypeArgumentSyntax
  makeFunctionTypeArgument(TypeSyntax TypeArgument);

  /// Make a function argument type syntax with all elements marked as missing.
  static FunctionTypeArgumentSyntax makeBlankFunctionArgumentType();

  /// Make a function type, for example, `(Int, Int) throws -> Int`
  static FunctionTypeSyntax
  makeFunctionType(TypeAttributesSyntax TypeAttributes,
                   RC<TokenSyntax> LeftParen,
                   TypeArgumentListSyntax ArgumentList,
                   RC<TokenSyntax> RightParen, RC<TokenSyntax> ThrowsOrRethrows,
                   RC<TokenSyntax> Arrow, TypeSyntax ReturnType);

  /// Make a function type with all elements marked as missing.
  static FunctionTypeSyntax makeBlankFunctionType();

  /// Make a list of type arguments with all elements marked as missing.
  static TypeArgumentListSyntax makeBlankTypeArgumentList();

#pragma mark - Generics

  /// Make an empty generic parameter clause.
  static GenericParameterClauseSyntax
  makeBlankGenericParameterClause();

  /// Make an empty generic argument clause.
  static GenericArgumentClauseSyntax makeBlankGenericArgumentClause();

  /// Make an empty generic where clause.
  static GenericWhereClauseSyntax makeBlankGenericWhereClause();

  /// Make a same-type requirement with the specified elements.
  ///
  /// Any elements are allowed to be marked as missing.
  static SameTypeRequirementSyntax
  makeSameTypeRequirement(TypeIdentifierSyntax LeftTypeIdentifier,
                          RC<TokenSyntax> EqualityToken, TypeSyntax RightType);

  /// Make a same-type requirement with all elements marked as missing.
  static SameTypeRequirementSyntax makeBlankSameTypeRequirement();

  /// Make an empty same-type-requirement with all missing elements.
  static SameTypeRequirementSyntax makeSameTypeRequirement();

  /// Make a generic parameter with the specified name and trivia.
  static GenericParameterSyntax
  makeGenericParameter(OwnedString TypeName, const Trivia &LeadingTrivia,
                       const Trivia &TrailingTrivia);

  /// Make a generic parameter with all elements marked as missing.
  static GenericParameterSyntax makeBlankGenericParameter();
};
} // end namespace syntax
} // end namespace swift
#endif // SWIFT_SYNTAX_SyntaxFactory_H
