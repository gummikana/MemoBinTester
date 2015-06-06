#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

//-----------------------------------------------------------------------------

inline void VectorLoadFromTxtFile( std::vector< std::string >& array, const std::string& filename )
{
	std::ifstream file( filename.c_str() );
	std::string temp;
	while( std::getline( file, temp ) ) 
	{
		array.push_back( temp );
	}

	file.close();
}

template< class T >
T CastFromString( const std::string& str )
{
	T result;
	std::stringstream ss( str );
	ss.operator>>( result );
	return result;
}

bool IsRed( const std::string& text )
{
	// a( text.empty() == false );
	const std::string substr = text.substr( 0, 2 );
	if( substr == "ri" ) return false;
	if( substr == "pa" ) return false;
	return true;
}

bool IsPicture( const std::string& text )
{
	// a( text.empty() == false );
	const std::string substr = text.substr( 2 );

	if( substr == "11" || substr == "12" || substr == "13" || substr == "1" ) 
		return true;
	
	return false;
}

bool IsHigherThan7( const std::string& text )
{
	// a( text.empty() == false );
	const std::string substr = text.substr( 2 );
	int n = CastFromString< int >( substr );

	if( (n % 2) == 0 ) return true;
		
	return false;
}

int GetAsNum( const std::vector< bool >& memo_deck, int p0, int p1, int p2 )
{
	p0 = p0 % (int)memo_deck.size();
	p1 = p1 % (int)memo_deck.size();
	p2 = p2 % (int)memo_deck.size();

	int b1 = memo_deck[p0] ? 1 : 0;
	int b2 = memo_deck[p1] ? 2 : 0;
	int b3 = memo_deck[p2] ? 4 : 0;
	return ( b1 | b2 | b3 );
}

bool HasDuplicates( const std::vector< int >& a )
{
	for( int i = 0; i < a.size(); ++i )
	{
		for( int j = i + 1; j < a.size(); ++j )
		{
			if( a[i] == a[j] )
				return true;
		}
	}

	return false;
}

int HowManyDuplicates( const std::vector< int >& a )
{
	int result = 0;
	for( int i = 0; i < a.size(); ++i )
	{
		for( int j = i + 1; j < a.size(); ++j )
		{
			if( a[i] == a[j] )
				result++;
		}
	}

	return result;
}

void FindHelpers()
{

	std::vector< std::string > memo_deck;
	VectorLoadFromTxtFile( memo_deck, "mnemonica.txt" );
	// std::cout << memo_deck.size() << std::endl;

	std::vector< bool > orig_redblack_deck( memo_deck.size() );

	for( std::size_t i = 0; i < memo_deck.size(); ++i )
	{
		orig_redblack_deck[i] = IsRed( memo_deck[i] );
	}

	/*for( int i0 = 0; i0 < 52; ++i0 )
	{
		for( int i1 = i0 + 1; i1 < 52; ++i1 )
		{

			std::vector< bool > redblack_deck = orig_redblack_deck;
			std::swap( redblack_deck[i0], redblack_deck[i1] );
*/
			std::vector< bool > redblack_deck = orig_redblack_deck;
			for( int i = 0; i < 8; ++i )
			{
				int result = GetAsNum( redblack_deck, i, 7 + i, 15 + i );
				std::cout << result << std::endl;
			}
			// return;
			
			
			// ok lets try to find this...
			std::vector< int > circ_buffer( 8 );
			for( int i = 0; i < 8; ++i ) 
				circ_buffer[i] = -1;
			// std::cout << HowManyDuplicates( circ_buffer ) << std::endl;


			int circ_buffer_i = 0;
			
			int min_duplicates = 8;
			int min_i = 0;
			int min_j = 0;
			int min_k = 0;

			const int size = (int)memo_deck.size();
			for( int i = 0; i < size; ++i )
			{
				for( int j = i + 1; j < size; ++j )
				{
					for( int k = j + 1; k < size; ++k )
					{
						for( int e = 0; e < 8; ++e )
						{
							int result = GetAsNum( redblack_deck, i + e, j + e, k + e );
							circ_buffer[ e ] = result;
						}
						int duplicates = HowManyDuplicates( circ_buffer );
						if( duplicates < min_duplicates )
						{
							min_duplicates = duplicates;
							min_i = i;
							min_j = j;
							min_k = k;
						}
						if( duplicates == 0 )
						{
							std::cout << "min_duplicates: " << min_duplicates << " - " <<  ( i + 1) << ", " << (j+1) << ", " << (k+1) << " --- ";
							for( int e = 0; e < 8; ++e )
							{
								std::cout << circ_buffer[e] << ", ";
							}
							std::cout << std::endl;
						}
					}
				}
			}
/*		}
	}*/

	// std::cout << "min_duplicates: " << min_duplicates << " - " <<  min_i << ", " << min_j << ", " << min_k << std::endl;
}

int main( int argc, char** args )
{
	FindHelpers();
	// std::cout << "hello world" << std::endl;
	return 0;
}
